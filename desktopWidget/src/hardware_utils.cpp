/****************************************************************************
** Copyright (c) 2019 Evgeny Teterin (nayk) <sutcedortal@gmail.com>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#include <QTimer>
#include <QEventLoop>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QStorageInfo>

#include <stdio.h>

#ifdef Q_OS_LINUX
#include <sys/times.h>
#include <unistd.h>
#include <time.h>
#endif

#ifdef Q_OS_WIN
#include <windows.h>
#include <psapi.h>
#endif

#include "SystemUtils"
#include "hardware_utils.h"

namespace hardware_utils { //===================================================

typedef struct proc_info_t {
    qreal usage[16];
} proc_info_t;

//==============================================================================
#ifdef Q_OS_WIN
//--------------------------------------------------------------
#pragma pack(push, 1)
struct SFMemory {
    quint16 version;
    quint16 flags;
    qint32 MemSize;
    qint32 handle;
    quint16 NumTemps;
    quint16 NumFans;
    quint16 NumVolts;
    qint32 temps[32];
    qint32 fans[32];
    qint32 volts[32];
};
#pragma pack(pop)

const LPCWSTR sf_filename = L"SFSharedMemory_ALM";
const LPCWSTR sf_mapname  = L"SFSharedMemory_ALM";
constexpr UINT sf_size = sizeof(SFMemory);

bool getTemperature(int index, qreal &temp)
{
    temp = 0.0;
    if((index < 0) || (index > 31)) return false;

    HANDLE file = static_cast<HANDLE>(CreateFile(sf_filename, GENERIC_READ | GENERIC_WRITE, 0,
            nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr));
    HANDLE filemap = static_cast<HANDLE>(CreateFileMapping(file, nullptr,
                                                           PAGE_READWRITE, 0, sf_size, sf_mapname));
    SFMemory* sfmemory = static_cast<SFMemory*>(MapViewOfFile(filemap, FILE_MAP_READ, 0, 0, sf_size));
    bool res = sfmemory;
    if(res)
        temp = static_cast<qreal>( sfmemory->temps[index] ) / 100.0;

    CloseHandle(filemap);
    CloseHandle(file);
    return res;
}
//--------------------------------------------------------------
static double CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
   static unsigned long long _previousTotalTicks = 0;
   static unsigned long long _previousIdleTicks = 0;

   unsigned long long totalTicksSinceLastTime = totalTicks-_previousTotalTicks;
   unsigned long long idleTicksSinceLastTime  = idleTicks-_previousIdleTicks;

   double ret = 1.0 - ((totalTicksSinceLastTime > 0)
                       ? (static_cast<double>(idleTicksSinceLastTime))/totalTicksSinceLastTime
                       : 0);

   _previousTotalTicks = totalTicks;
   _previousIdleTicks  = idleTicks;
   return ret * 100.0;
}
//--------------------------------------------------------------
static unsigned long long FileTimeToInt64(const FILETIME &ft)
{
    return ((static_cast<unsigned long long>(ft.dwHighDateTime))<<32)
            | (static_cast<unsigned long long>(ft.dwLowDateTime));
}
//--------------------------------------------------------------
int getProcessorLoad(proc_info_t *info)
{
    int count = 1;

    FILETIME idleTime, kernelTime, userTime;
    info->usage[0] = GetSystemTimes(&idleTime, &kernelTime, &userTime) ?
                CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime)
                                 + FileTimeToInt64(userTime))
              : -1.0;

    for(int k = 1; k < 16; k++) {
        info->usage[k] = info->usage[0];
    }

    return count + cpuCount();
}
//--------------------------------------------------------------
#endif
//==============================================================================
#ifdef Q_OS_LINUX
int getProcessorLoad(proc_info_t *info)
{
    int count = 0;
    static unsigned int pre_total[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    static unsigned int pre_used[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    unsigned int cpu[16], nice[16], system[16], idle[16];

    FILE *fp;
    if (!(fp = fopen("/proc/stat", "r"))) {
        return 0;
    }

    char name[1024];
    while(fgets(name, sizeof(name)-1, fp) && count<16) {
        if((name[0] != 'c') || (name[1] != 'p') || (name[2] != 'u')) break;
        sscanf(name, "%*s %u %u %u %u", &cpu[count], &nice[count],
               &system[count], &idle[count]);
        count++;
    }
    fclose(fp);

    unsigned int used[16];
    unsigned int total[16];
    for(int k = 0; k < count; k++) {
        used[k] = cpu[k] + system[k] + nice[k];
        total[k] = cpu[k] + nice[k] + system[k] + idle[k];
    }

    for(int k = 0; k < count; k++) {
        if((pre_total[k] == 0)||(pre_used[k] == 0)) {
            info->usage[k] = 0.0;
        }
        else {
            info->usage[k] = ((100.0 * static_cast<qreal>(used[k] - pre_used[k]))
                              / static_cast<qreal>((total[k] - pre_total[k])));
        }

        pre_used[k] = used[k];
        pre_total[k] = total[k];
    }

    return count;
}
#endif
//==============================================================================
#ifdef Q_OS_LINUX
bool getDiskIOLoad(const QString &dev, double &io)
{
    FILE *fp;
    if (!(fp = fopen("/proc/diskstats", "r"))) {
        return false;
    }

    bool res = false;
    char name[1024];
    while(fgets(name, sizeof(name)-1, fp) ) {
        QString str(name);
        if( !str.contains( " " + dev + " " ) ) continue;
        QStringList sl = str.split( " ", QString::SkipEmptyParts );
        if( sl.size() < 10 ) break;
        bool ok;
        qint64 sectors = QString( sl.at(5) ).toLongLong(&ok);
        if(!ok) break;
        sectors += QString( sl.at(9) ).toLongLong(&ok);
        if(!ok) break;
        io = sectors/2.0;
        res = true;
    }
    fclose(fp);
    return res;
}
//==============================================================================
bool getNetInfo(const QString &iface, double &rxKB, double &txKB)
{
    FILE *fp;
    if (!(fp = fopen("/proc/net/dev", "r"))) {
        return false;
    }

    bool res = false;
    char name[1024];
    while(fgets(name, sizeof(name)-1, fp) ) {
        QString str(name);
        if( !str.contains( iface + ":" ) ) continue;
        QStringList sl = str.split( " ", QString::SkipEmptyParts );
        if( sl.size() < 10 ) break;
        bool ok;
        quint64 rx = QString( sl.at(1) ).toULongLong(&ok);
        if(!ok) break;
        quint64 tx = QString( sl.at(9) ).toULongLong(&ok);
        if(!ok) break;

        rxKB = static_cast<qreal>(rx)/1024.0;
        txKB = static_cast<qreal>(tx)/1024.0;

        res = true;
        break;
    }
    fclose(fp);
    return res;
}
//==============================================================================
quint64 getMemValueFromStr(const QString &str)
{
    int n = str.indexOf(" ");
    if(n < 1) return 0;
    bool ok;
    quint64 val = str.mid(0, n).trimmed().toULongLong(&ok);
    if(!ok) return 0;
    QString ed = str.mid(n).trimmed().toLower().left(1);
    if(ed == "b") val /= 1024;
    else if(ed == "m") val *= 1024;
    else if(ed == "g") val *= 1024*1024;
    return val;
}
#endif
//==============================================================================
int cpuCount()
{
    return QThread::idealThreadCount();
}
//==============================================================================
bool cpuLoadPercent(QVector<qreal> &vecLoad, quint8 intervalMS)
{
    proc_info_t info;
    int load = getProcessorLoad(&info);
    if(intervalMS > 0) {
        system_utils::pause(intervalMS);
        load = getProcessorLoad(&info);
    }

    for(int i=0; i<load; ++i) {

        if(i < vecLoad.size())
            vecLoad[i] = info.usage[i];
        else
            vecLoad.append( info.usage[i] );
    }

    return true;
}
//==============================================================================
bool memInfo(quint64 &memTotalKB, quint64 &memFreeKB, quint64 &memAvailableKB,
                 quint64 &swapTotalKB, quint64 &swapFreeKB)
{
    memTotalKB = 0;
    memFreeKB = 0;
    swapTotalKB = 0;
    swapFreeKB = 0;
    memAvailableKB = 0;

#if defined (Q_OS_WIN)

    MEMORYSTATUSEX memStatusEx;
    memStatusEx.dwLength = sizeof(memStatusEx);
    if(!GlobalMemoryStatusEx(&memStatusEx)) return false;

    memTotalKB = memStatusEx.ullTotalPhys / 1024;
    memAvailableKB = memStatusEx.ullAvailPhys / 1024;
    memFreeKB = memAvailableKB;
    swapTotalKB = ( memStatusEx.ullTotalPageFile - memStatusEx.ullTotalPhys ) / 1024;
    swapFreeKB = ( memStatusEx.ullAvailPageFile - memStatusEx.ullAvailPhys ) / 1024;

#elif defined (Q_OS_LINUX)

    FILE *fp;
    if (!(fp = fopen("/proc/meminfo", "r"))) {
        return false;
    }

    char name[512];
    while(fgets(name, sizeof(name)-1, fp)) {
        QString str(name);

        if(str.indexOf("MemTotal:") == 0) {
            memTotalKB = getMemValueFromStr(str.mid(9).trimmed());
        }
        else if(str.indexOf("MemFree:") == 0) {
            memFreeKB = getMemValueFromStr(str.mid(8).trimmed());
        }
        else if(str.indexOf("MemAvailable:") == 0) {
            memAvailableKB = getMemValueFromStr(str.mid(13).trimmed());
        }
        else if(str.indexOf("SwapTotal:") == 0) {
            swapTotalKB = getMemValueFromStr(str.mid(10).trimmed());
        }
        else if(str.indexOf("SwapFree:") == 0) {
            swapFreeKB = getMemValueFromStr(str.mid(9).trimmed());
        }
    }
    fclose(fp);

#endif
    return true;
}
//==============================================================================
bool diskInfo(const QString &dev, quint64 &sizeKB, quint64 &freeKB)
{
    sizeKB = 0;
    freeKB = 0;

    QStorageInfo storageInfo(dev);
    if(!storageInfo.isValid() || !storageInfo.isReady()) return false;
    sizeKB = static_cast<quint64>(storageInfo.bytesTotal() / 1024 );
    freeKB = static_cast<quint64>(storageInfo.bytesFree() / 1024 );

    return true;
}
//==============================================================================
bool diskIOKB(const QString &dev, qreal &ioKB)
{
    ioKB = 0.0;

#if defined (Q_OS_WIN)

    Q_UNUSED(dev)

#elif defined (Q_OS_LINUX)
    return getDiskIOLoad(dev, ioKB);
#endif
    return true;
}
//==============================================================================
bool netInfo(const QString &iface, qreal &rxKB, qreal &txKB
             #ifdef Q_OS_WIN
             , QString &err
             #endif
             )
{
    rxKB = 0;
    txKB = 0;

#if defined (Q_OS_WIN)

    Q_UNUSED(iface)

    QString out;
    if(!system_utils::osCmd("netstat -e", out, 1000)) {
        err = out;
        return false;
    }
    QStringList list = out.split("\r\n", QString::SkipEmptyParts);
    if (list.size() < 3) {
        err = "Error out format";
        return false;
    }
    list = list.at(2).split(" ", QString::SkipEmptyParts);
    if (list.size() < 3) {
        err = "Data not found";
        return false;
    }

    bool ok;
    int rx = list.at(1).toInt(&ok);
    if(!ok) {
        err = "Rx not int";
        return false;
    }
    int tx = list.at(2).toInt(&ok);
    if(!ok) {
        err = "Tx not int";
        return false;
    }

    rxKB = static_cast<qreal>(rx) / 1024.0;
    txKB = static_cast<qreal>(tx) / 1024.0;
    return true;
#elif defined (Q_OS_LINUX)
    return getNetInfo(iface, rxKB, txKB);

#endif
}
//==============================================================================
bool getMeMemoryUsage(qint64 &pageFileUsage, qint64 &ramUsage)
{
#if defined (Q_OS_WIN)

    PROCESS_MEMORY_COUNTERS pmc;
    WINBOOL res = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    if(res) {

        pageFileUsage = static_cast<qint64>( pmc.PagefileUsage );
        ramUsage = static_cast<qint64>( pmc.WorkingSetSize );
        return true;
    }

#elif defined (Q_OS_LINUX)
    Q_UNUSED(pageFileUsage)
    Q_UNUSED(ramUsage)

#endif
    return false;
}
//==============================================================================
bool getMeMemoryUsage(qreal &pageFileUsageKB, qreal &ramUsageKB)
{
    qint64 n1 = 0, n2 = 0;
    if(!getMeMemoryUsage(n1, n2)) return false;

    pageFileUsageKB = static_cast<qreal>(n1)  / 1024.0;
    ramUsageKB = static_cast<qreal>(n2)  / 1024.0;
    return true;
}
//==============================================================================
bool getMeMemoryUsage(QString &infoStr)
{
    infoStr = "";
#if defined (Q_OS_WIN)

    PROCESS_MEMORY_COUNTERS pmc;
    WINBOOL res = GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    if(res) {

        infoStr = QString("PageFaultCount: %1\n"
                          "PeakWorkingSetSize: %2 B\n"
                          "WorkingSetSize: %3 B\n"
                          "QuotaPeakPagedPoolUsage: %4 B\n"
                          "QuotaPagedPoolUsage: %5 B\n"
                          "QuotaPeakNonPagedPoolUsage: %6 B\n"
                          "QuotaNonPagedPoolUsage: %7 B\n"
                          "PagefileUsage: %8 B\n"
                          "PeakPagefileUsage: %9 B"
                          )
                .arg(static_cast<qint64>( pmc.PageFaultCount ) )
                .arg(static_cast<qint64>( pmc.PeakWorkingSetSize ))
                .arg(static_cast<qint64>( pmc.WorkingSetSize ))
                .arg(static_cast<qint64>( pmc.QuotaPeakPagedPoolUsage ))
                .arg(static_cast<qint64>( pmc.QuotaPagedPoolUsage ))
                .arg(static_cast<qint64>( pmc.QuotaPeakNonPagedPoolUsage ))
                .arg(static_cast<qint64>( pmc.QuotaNonPagedPoolUsage ))
                .arg(static_cast<qint64>( pmc.PagefileUsage ))
                .arg(static_cast<qint64>( pmc.PeakPagefileUsage ))
                ;

        return true;
    }

#elif defined (Q_OS_LINUX)

#endif
    return false;
}

} // namespace hardware_utils //================================================


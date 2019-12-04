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
#include <QProcess>

#if defined (Q_OS_WIN32)
#include <windows.h>
#include <versionhelpers.h>
#elif defined (Q_OS_LINUX)
#include <unistd.h>
#include <sys/utsname.h>
#endif

#include "system_utils.h"

namespace system_utils { //=====================================================

void pause(int ms)
{
    QTimer timer;
    timer.setInterval(ms == 0 ? 1 : qAbs(ms));
    timer.setSingleShot(true);
    QEventLoop loop;
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();
}
//==============================================================================
int dayOfWeek(int year, int month, int day)
{
    if(year <= 1752)
        return -1;

    if((month < 1) || (month > 12))
        return -1;

    if((day < 1) || (day > 31))
        return -1;

    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= month < 3;
    int dow = (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;

    if(dow == 0)
        dow = 7;
    else if(( dow < 0 ) || ( dow > 7 ))
        return -1;

    return dow;
}
//==============================================================================
bool osCmd(const QString &cmd, QString &out, int timeout)
{
    QProcess process;

#if defined (Q_OS_WIN32)
    process.start(QString("%1").arg(cmd));
    //process.start(QString("cmd -c \"%1\"").arg(cmd));
#else
    process.start(QString("bash -c \"%1\"").arg(cmd));
#endif

    timeout = qBound(300, timeout, 300000);
    if (!process.waitForStarted(timeout)) {
        out = QObject::tr("Process start timeout");
        return false;
    }
    if (!process.waitForFinished(timeout)) {
        out = QObject::tr("Timeout waiting for process to complete");
        return false;
    }
    out = QString(process.readAllStandardOutput()).trimmed();
    return true;
}
//==============================================================================
QString osName()
{
    QString res = "";

#if defined (Q_OS_WIN32)
    res = "Windows";
#elif defined (Q_OS_LINUX)
    res = "Linux";
#elif defined (Q_OS_MACOS)
    res = "MacOS";
#elif defined (Q_OS_UNIX)
    res = "Unix";
#endif

    return res;
}
//==============================================================================
QString osVersion()
{
    QString res = "";

#if defined (Q_OS_WIN32)
    if (IsWindowsServer()) return "Server";
    if (IsWindows10OrGreater()) return "10";
    if (IsWindows8Point1OrGreater()) return "8.1";
    if (IsWindows8OrGreater())return "8";
    if (IsWindows7SP1OrGreater()) return "7 SP1";
    if (IsWindows7OrGreater()) return "7";
    if (IsWindowsVistaOrGreater()) return "Vista";
    if (IsWindowsXPOrGreater()) return "XP";
#elif defined (Q_OS_LINUX)
    utsname kernelInfo;
    uname(&kernelInfo);
    res = QString(kernelInfo.release);
#endif

    return res;
}

} // namespace system_utils //==================================================


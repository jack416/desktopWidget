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
#ifndef HARDWARE_UTILS_H
#define HARDWARE_UTILS_H

#include <QtCore>

namespace hardware_utils { //===================================================

int cpuCount();
bool cpuLoadPercent(QVector<qreal> &vecLoad, quint8 intervalMS=0);
bool memInfo(quint64 &memTotalKB, quint64 &memFreeKB, quint64 &memAvailableKB,
             quint64 &swapTotalKB, quint64 &swapFreeKB);
bool diskInfo(const QString &dev, quint64 &sizeKB, quint64 &freeKB);
bool diskIOKB(const QString &dev, qreal &ioKB);
bool netInfo(const QString &iface, qreal &rxKB, qreal &txKB
             #ifdef Q_OS_WIN
             , QString &err
             #endif
             );
bool getMeMemoryUsage(qint64 &pageFileUsage, qint64 &ramUsage);
bool getMeMemoryUsage(qreal &pageFileUsageKB, qreal &ramUsageKB);
bool getMeMemoryUsage(QString &infoStr);

#ifdef Q_OS_WIN
bool getTemperature(int index, qreal &temp);
#endif

} // namespace hardware_utils //================================================
#endif // HARDWARE_UTILS_H

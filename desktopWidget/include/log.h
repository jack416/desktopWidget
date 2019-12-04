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
#ifndef LOGSAVER_H
#define LOGSAVER_H

#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

namespace nayk { //=============================================================

//==============================================================================
class Log : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool debugSave READ debugSave WRITE setDebugSave NOTIFY debugSaveChanged)
    Q_PROPERTY(QString logFileName READ logFileName CONSTANT)
    Q_PROPERTY(QString logDir READ logDir CONSTANT)
    Q_PROPERTY(QString lastError READ lastError NOTIFY error)

public:
    enum LogType {
        LogInfo = 0,
        LogWarning,
        LogError,
        LogIn,
        LogOut,
        LogText,
        LogDbg,
        LogOther
    };
    Q_ENUM(LogType)

    explicit Log(QObject *parent = nullptr);
    explicit Log(QDateTime startTime, QObject *parent = nullptr);
    explicit Log(const QString &logDir, QDateTime startTime = QDateTime::currentDateTime(),
                 QObject *parent = nullptr);
    explicit Log(const QString &logDir, const QString &fileName,
                 QDateTime startTime = QDateTime::currentDateTime(), QObject *parent = nullptr);
    virtual ~Log();
    void setDebugSave(bool enable = true);
    bool debugSave() const;
    QString logDir() const;
    QString logFileName() const;
    QString lastError() const;
    static QString getLogTypeStr(LogType logType);
    static QString getLogPrefix(LogType logType,
                                const QDateTime &date = QDateTime::currentDateTime());
    static LogType strToLogType(const QString &typeStr);
    void deleteOldLogFiles(const QString &fileMask = QString("*.log"), int maxCount = 10);

private:
    const QString defaultLogDirName {"log"};
    QDateTime m_startTime;
    QString m_fileName {""};
    QString m_logDir {""};
    QFile m_file;
    QTextStream m_stream;
    QString m_lastError {""};
    bool m_dbgSave {true};
    bool writeFirstLine();
    bool writeLastLine();
    void startLog(const QString &fileName = QString());

signals:
    void openFile(const QString &fileName);
    void closeFile(const QString &fileName);
    void debugSaveChanged(bool enable);
    void error(const QString &errorText);
    void write(const QString &text);

public slots:
    void saveToLog(const QString &text, LogType logType = LogInfo);
};
//==============================================================================

} // namespace nayk //==========================================================
#endif // LOGSAVER_H

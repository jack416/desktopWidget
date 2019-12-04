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
#ifndef FILE_SYS_H
#define FILE_SYS_H

#include <QString>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace file_sys { //=========================================================

const QChar directorySeparator = '/';

//==============================================================================

bool directoryExists(const QString &dirName);
bool fileExists(const QString &fileName);
bool makePath(const QString &path);
QString changeFileExt(const QString &fileName, const QString &newExt);
QString extractFileExt(const QString &fileName, bool withDot = true);
QString extractFileName(const QString &fileName);
QString extractFilePath(const QString &fileName);
bool readJsonFromFile(const QString &fileName, QJsonDocument &json, QString &errorString);
bool readJsonFromFile(const QString &fileName, QJsonArray &json, QString &errorString);
bool readJsonFromFile(const QString &fileName, QJsonObject &json, QString &errorString);
bool writeJsonToFile(const QString &fileName, const QJsonDocument &json, QString &errorString);
bool writeJsonToFile(const QString &fileName, const QJsonArray &json, QString &errorString);
bool writeJsonToFile(const QString &fileName, const QJsonObject &json, QString &errorString);

} // namespace file_sys //======================================================
#endif // FILE_SYS_H

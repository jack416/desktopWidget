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
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>

#include "file_sys.h"

namespace file_sys { //=========================================================

bool directoryExists(const QString &dirName)
{
    QFileInfo dir(dirName);
    return dir.exists() && dir.isDir();
}
//==============================================================================
bool fileExists(const QString &fileName)
{
    QFileInfo file(fileName);
    return file.exists() && file.isFile();
}
//==============================================================================
bool makePath(const QString &path)
{
    QDir dir;
    return dir.mkpath(path);
}
//==============================================================================
QString changeFileExt(const QString &fileName, const QString &newExt)
{
    int i = fileName.lastIndexOf('.');

    if( newExt.length() > 0 ) {
        if(newExt[0] == '.') {
            return ((i>0) ? fileName.left( i ) : fileName) + newExt;
        }
        else {
            return ((i>0) ? fileName.left( i ) : fileName) + "." + newExt;
        }
    }
    else {
        return fileName;
    }
}
//==============================================================================
QString extractFileExt(const QString &fileName, bool withDot)
{
    QString f = extractFileName(fileName);
    int i = f.lastIndexOf('.');

    if(i >= 0) {
        if(withDot) {
            return f.right( f.length() - i );
        }
        else {
            return f.right( f.length() - i - 1 );
        }
    }
    else {
        return "";
    }
}
//==============================================================================
QString extractFileName(const QString &fileName)
{
    QString f = QDir::fromNativeSeparators(fileName);

    while((f.length()>0) && (f[f.length()-1] == directorySeparator)) {
        f.remove(f.length()-1,1);
    }

    int i;

#if defined (Q_OS_WIN32)
    i = f.indexOf(':');
    if(i >= 0) f.remove(0, i+1);
#endif

    i = f.lastIndexOf( directorySeparator );
    if(i>=0) f.remove(0, i+1);
    return f;
}
//==============================================================================
QString extractFilePath(const QString &fileName)
{
   QString f = QDir::fromNativeSeparators(fileName);
   int i = f.lastIndexOf( directorySeparator );
   return (i >= 0) ? f.left(i+1) : "";
}
//==============================================================================
bool readJsonFromFile(const QString &fileName, QJsonDocument &json, QString &errorString)
{
    errorString = "";
    QFile file( fileName );

    if(!file.exists()) {
        errorString =  QObject::tr("File \"%1\" does not exist")
                .arg(extractFileName( fileName ));
        return false;
    }

    if(!file.open(QFile::ReadOnly)) {
        errorString = QObject::tr("Failed to open file \"%1\" for reading")
                .arg( extractFileName( fileName ) );
        return false;
    }

    QJsonParseError parseError;
    json = QJsonDocument::fromJson( file.readAll(), &parseError );
    file.close();

    if(parseError.error != QJsonParseError::NoError) {
        errorString = QObject::tr("File \"%1\" parsing error:")
                .arg( extractFileName( fileName ) ) + "\n" + parseError.errorString();
        return false;
    }

    return true;
}
//==============================================================================
bool readJsonFromFile(const QString &fileName, QJsonArray &json, QString &errorString)
{
    QJsonDocument doc;
    if(!readJsonFromFile(fileName, doc, errorString)) return false;

    if(!doc.isArray()) {
        errorString = QObject::tr("File \"%1\" is not JSON array")
                .arg( extractFileName( fileName ) );
        return false;
    }

    json = doc.array();
    return true;
}
//==============================================================================
bool readJsonFromFile(const QString &fileName, QJsonObject &json, QString &errorString)
{
    QJsonDocument doc;
    if(!readJsonFromFile(fileName, doc, errorString)) return false;

    if(!doc.isObject()) {
        errorString = QObject::tr("File \"%1\" is not JSON object")
                .arg( extractFileName( fileName ) );
        return false;
    }

    json = doc.object();
    return true;
}
//==============================================================================
bool writeJsonToFile(const QString &fileName, const QJsonDocument &json, QString &errorString)
{
    errorString = "";

    QFile file( fileName );

    if(!file.open(QFile::WriteOnly)) {
        errorString = QObject::tr("Failed to open file \"%1\" for writing")
                .arg( extractFileName( fileName ) );
        return false;
    }

    QByteArray buf = json.toJson();
    int n = static_cast<int>(file.write( buf ));
    bool res = file.flush();
    file.close();

    if(n != buf.size()) {
        errorString = QObject::tr("Failed to write all data to file \"%1\"")
                .arg( extractFileName( fileName ) );
        return false;
    }

    if(!res) {
        errorString = QObject::tr("Failed to save data to file \"%1\"")
                .arg( extractFileName( fileName ) );
        return false;
    }

    return true;
}
//==============================================================================
bool writeJsonToFile(const QString &fileName, const QJsonArray &json, QString &errorString)
{
    return writeJsonToFile(fileName, QJsonDocument(json), errorString);
}
//==============================================================================
bool writeJsonToFile(const QString &fileName, const QJsonObject &json, QString &errorString)
{
    return writeJsonToFile(fileName, QJsonDocument(json), errorString);
}

} // namespace file_sys //======================================================


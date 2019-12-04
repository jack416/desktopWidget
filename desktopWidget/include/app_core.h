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
#ifndef APP_CORE_H
#define APP_CORE_H

#include <QtCore>

namespace app_core { //=========================================================

bool initializeApplication(const QString &applicationName,
                           const QString &organizationName = QString(),
                           const QString &organizationDomain = QString());
void installTranslations(const QString &translationsDir = QString("translations"),
                         const QString &language = QString());
QString applicationVersion();
QString applicationBuildDate();
QString applicationFullPath();
QString applicationRootPath();
QString applicationProfilePath();
bool parameterExists(const QString &name, const QString &shortName = QString(),
                     QString *value = nullptr);
bool checkVersionQuery();

} // namespace app_core //======================================================
#endif // APP_CORE_H

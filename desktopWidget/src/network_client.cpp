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
#include <QEventLoop>
#include <QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

#include "network_client.h"

namespace network_client { //===================================================


constexpr int requestTimeOut = 4000;

//==============================================================================
bool simpleGet(const QString &url, QString &resultString)
{
    bool res { false };
    QEventLoop loop;
    QTimer timer;
    timer.setInterval( requestTimeOut );
    timer.setSingleShot(true);

    QNetworkRequest request { QUrl { url } };
    QNetworkAccessManager manager;
    QNetworkReply* reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    QObject::connect(&timer, &QTimer::timeout, reply, &QNetworkReply::abort);

    timer.start();
    loop.exec();
    timer.stop();

    if (reply->isFinished() && reply->error() == QNetworkReply::NoError) {

        resultString = QString( reply->readAll() ).trimmed();
        res = true;
    }
    else {

        resultString = QString( reply->errorString() ).trimmed();
        res = false;
    }

    reply->deleteLater();
    return res;
}
//==============================================================================
bool externalIP(QString &ip)
{
    static QStringList urls = { "https://icanhazip.com", "https://api.ipify.org",
                                "http://smart-ip.net/myip", "http://api.ipify.org",
                                "http://grio.ru/myip.php", "http://ifconfig.me/ip" };
    for(auto i=0; i<urls.size(); ++i) {
        if(simpleGet( urls.at(i), ip )) {

            QStringList ip4 = ip.split('.', QString::SkipEmptyParts);
            if(ip4.size() != 4) continue;
            bool okIP = true;
            for(auto j=0; j<ip4.size(); j++) {
                bool ok;
                int n = QString(ip4.at(j)).toInt(&ok, 10);
                okIP = okIP && ok && (n>=0) && (n<=255);
                if(!okIP) break;
            }
            if(okIP) return true;
        }
    }
    return false;
}

} // namespace//================================================================

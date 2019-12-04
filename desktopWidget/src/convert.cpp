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
#include "convert.h"

namespace convert { //==========================================================

quint8 bcdEncode(qint8 value)
{
    QString s = (value < 0) ? "F" : "";
    s += QString::number( qAbs(value) );
    return static_cast<quint8>( s.toUInt(nullptr, 16) );
}
//==============================================================================
quint16 bcdEncode(qint16 value)
{
    QString s = (value < 0) ? "F" : "";
    s += QString::number( qAbs(value) );
    return static_cast<quint16>( s.toUInt(nullptr, 16) );
}
//==============================================================================
quint32 bcdEncode(qint32 value)
{
    QString s = (value < 0) ? "F" : "";
    s += QString::number( qAbs(value) );
    return static_cast<quint32>( s.toULong(nullptr, 16) );
}
//==============================================================================
quint64 bcdEncode(qint64 value)
{
    QString s = (value < 0) ? "F" : "";
    s += QString::number( qAbs(value) );
    return static_cast<quint64>( s.toULongLong(nullptr, 16) );
}
//==============================================================================
quint8 bcdEncode(quint8 value)
{
    QString s = QString::number( value );
    return static_cast<quint8>( s.toUInt(nullptr, 16) );
}
//==============================================================================
quint16 bcdEncode(quint16 value)
{
    QString s = QString::number( value );
    return static_cast<quint16>( s.toUInt(nullptr, 16) );
}
//==============================================================================
quint32 bcdEncode(quint32 value)
{
    QString s = QString::number( value );
    return static_cast<quint32>( s.toULong(nullptr, 16) );
}
//==============================================================================
quint64 bcdEncode(quint64 value)
{
    QString s = QString::number( value );
    return static_cast<quint64>( s.toULongLong(nullptr, 16) );
}
//==============================================================================
qint8 bcdDecode(quint8 bcdValue, bool *ok)
{
    QString s = intToHex( bcdValue, 2, false );

    while( (s.length() > 1) && (s.left(1) == "0"))
        s.remove(0,1);

    if(s.left(1).toUpper() == "F")
        s[0] = QChar('-');

    return static_cast<qint8>(s.toInt(ok, 10));
}
//==============================================================================
qint16 bcdDecode(quint16 bcdValue, bool *ok)
{
    QString s = intToHex( bcdValue, 4, false );

    while( (s.length() > 1) && (s.left(1) == "0"))
        s.remove(0,1);

    if(s.left(1).toUpper() == "F")
        s[0] = QChar('-');

    return static_cast<qint16>(s.toInt(ok, 10));
}
//==============================================================================
qint32 bcdDecode(quint32 bcdValue, bool *ok)
{
    QString s = intToHex( bcdValue, 8, false );

    while( (s.length() > 1) && (s.left(1) == "0"))
        s.remove(0,1);

    if(s.left(1).toUpper() == "F")
        s[0] = QChar('-');

    return static_cast<qint32>(s.toLong(ok, 10));
}
//==============================================================================
qint64 bcdDecode(quint64 bcdValue, bool *ok)
{
    QString s = intToHex( bcdValue, 16, false );

    while( (s.length() > 1) && (s.left(1) == "0"))
        s.remove(0,1);

    if(s.left(1).toUpper() == "F")
        s[0] = QChar('-');

    return static_cast<qint64>(s.toLongLong(ok, 10));
}
//==============================================================================
quint8 bcdDecodeUnsigned(quint8 bcdValue, bool *ok)
{
    QString s = intToHex( bcdValue, 2, false );
    return static_cast<quint8>(s.toUInt(ok, 10));
}
//==============================================================================
quint16 bcdDecodeUnsigned(quint16 bcdValue, bool *ok)
{
    QString s = intToHex( bcdValue, 4, false );
    return static_cast<quint16>(s.toUInt(ok, 10));
}
//==============================================================================
quint32 bcdDecodeUnsigned(quint32 bcdValue, bool *ok)
{
    QString s = intToHex( bcdValue, 8, false );
    return static_cast<quint32>(s.toULong(ok, 10));
}
//==============================================================================
quint64 bcdDecodeUnsigned(quint64 bcdValue, bool *ok)
{
    QString s = intToHex( bcdValue, 16, false );
    return static_cast<quint64>(s.toULongLong(ok, 10));
}
//==============================================================================
QString intToHex(quint8 val, int len, bool withPrefix)
{
    QString prefix = withPrefix ? "0x" : "";
    QString res = QString::number(val, 16);

    while(res.length() < len)
        res = "0" + res;

    return prefix + res.toUpper().right(len);
}
//==============================================================================
QString intToHex(qint8 val, int len, bool withPrefix)
{
    return intToHex( static_cast<quint8>(val), len, withPrefix );
}
//==============================================================================
QString intToHex(quint16 val, int len, bool withPrefix)
{
    QString prefix = withPrefix ? "0x" : "";
    QString res = QString::number(val, 16);

    while(res.length() < len)
        res = "0" + res;

    return prefix + res.toUpper().right(len);
}
//==============================================================================
QString intToHex(qint16 val, int len, bool withPrefix)
{
    return intToHex( static_cast<quint16>(val), len, withPrefix );
}
//==============================================================================
QString intToHex(quint32 val, int len, bool withPrefix)
{
    QString prefix = withPrefix ? "0x" : "";
    QString res = QString::number(val, 16);

    while(res.length() < len)
        res = "0" + res;

    return prefix + res.toUpper().right(len);
}
//==============================================================================
QString intToHex(qint32 val, int len, bool withPrefix)
{
    return intToHex( static_cast<quint32>(val), len, withPrefix );
}
//==============================================================================
QString intToHex(quint64 val, int len, bool withPrefix)
{
    QString prefix = withPrefix ? "0x" : "";
    QString res = QString::number(val, 16);

    while(res.length() < len)
        res = "0" + res;

    return prefix + res.toUpper().right(len);
}
//==============================================================================
QString intToHex(qint64 val, int len, bool withPrefix)
{
    return intToHex( static_cast<quint64>(val), len, withPrefix );
}
//==============================================================================
quint8 lo(quint16 val)
{
    return static_cast<quint8>( val & 0x00FF );
}
//==============================================================================
qint8 lo(qint16 val)
{
    return static_cast<qint8>( lo( static_cast<quint16>(val)) );
}
//==============================================================================
quint16 lo(quint32 val)
{
    return static_cast<quint16>( val & 0x0000FFFF );
}
//==============================================================================
qint16 lo(qint32 val)
{
    return static_cast<qint16>( lo( static_cast<quint32>(val)) );
}
//==============================================================================
quint32 lo(quint64 val)
{
    return static_cast<quint32>( val & 0x00000000FFFFFFFF );
}
//==============================================================================
qint32 lo(qint64 val)
{
    return static_cast<qint32>( lo( static_cast<quint64>(val)) );
}
//==============================================================================
quint8 hi(quint16 val)
{
    return static_cast<quint8>( (val & 0xFF00) >> 8 );
}
//==============================================================================
qint8 hi(qint16 val)
{
    return static_cast<qint8>( hi( static_cast<quint16>(val)) );
}
//==============================================================================
quint16 hi(quint32 val)
{
    return static_cast<quint16>( (val & 0xFFFF0000) >> 16 );
}
//==============================================================================
qint16 hi(qint32 val)
{
    return static_cast<qint16>( hi( static_cast<quint32>(val)) );
}
//==============================================================================
quint32 hi(quint64 val)
{
    return static_cast<quint32>( (val & 0xFFFFFFFF00000000) >> 32 );
}
//==============================================================================
qint32 hi(qint64 val)
{
    return static_cast<qint32>( hi( static_cast<quint64>(val)) );
}
//==============================================================================
quint16 reverseBytes(quint16 val)
{
    return static_cast<quint16>(((val & static_cast<quint16>(0x00FF)) << 8)
            | ((val & static_cast<quint16>(0xFF00)) >> 8));
}
//==============================================================================
qint16 reverseBytes(qint16 val)
{
    return static_cast<qint16>( reverseBytes( static_cast<quint16>(val)) );
}
//==============================================================================
quint32 reverseBytes(quint32 val)
{
    return ((val & 0x000000FF) << 24) | ((val & 0x0000FF00) << 8) |
            ((val & 0xFF000000) >> 24) | ((val & 0x00FF0000) >> 8);
}
//==============================================================================
qint32 reverseBytes(qint32 val)
{
    return static_cast<qint32>( reverseBytes( static_cast<quint32>(val)) );
}
//==============================================================================
quint64 reverseBytes(quint64 val)
{
    return (( val & 0x00000000000000FF) << 56) | ((val & 0x000000000000FF00) << 40) |
            ((val & 0x0000000000FF0000) << 24) | ((val & 0x00000000FF000000) << 8)  |
            ((val & 0x000000FF00000000) >> 8)  | ((val & 0x0000FF0000000000) >> 24) |
            ((val & 0x00FF000000000000) >> 40) | ((val & 0xFF00000000000000) >> 56);
}
//==============================================================================
qint64 reverseBytes(qint64 val)
{
    return static_cast<qint64>( reverseBytes( static_cast<quint64>(val)) );
}
//==============================================================================
qint8 strToIntDef(const QString &str, qint8 defaultValue)
{
    bool ok=false;
    int base = 10;
    QString val = str.trimmed();

    if ((val.length() > 2) && (val.left(2).toLower() == "0x")) {
        base = 16;
        val.remove(0,2);
    }

    int n = val.toInt(&ok, base);

    if (ok)
        return static_cast<qint8>(n);
    else
        return defaultValue;
}
//==============================================================================
quint8 strToIntDef(const QString &str, quint8 defaultValue)
{
    return static_cast<quint8>( strToIntDef(str, static_cast<qint8>(defaultValue)) );
}
//==============================================================================
qint16 strToIntDef(const QString &str, qint16 defaultValue)
{
    bool ok=false;
    int base = 10;
    QString val = str.trimmed();

    if ((val.length() > 2) && (val.left(2).toLower() == "0x")) {
        base = 16;
        val.remove(0,2);
    }

    qint16 n = val.toShort(&ok, base);

    if (ok)
        return n;
    else
        return defaultValue;
}
//==============================================================================
quint16 strToIntDef(const QString &str, quint16 defaultValue)
{
    bool ok=false;
    int base = 10;
    QString val = str.trimmed();

    if ((val.length() > 2) && (val.left(2).toLower() == "0x")) {
        base = 16;
        val.remove(0,2);
    }

    quint16 n = val.toUShort(&ok, base);
    if (ok)
        return n;
    else
        return defaultValue;
}
//==============================================================================
qint32 strToIntDef(const QString &str, qint32 defaultValue)
{
    bool ok=false;
    int base = 10;
    QString val = str.trimmed();

    if ((val.length() > 2) && (val.left(2).toLower() == "0x")) {
        base = 16;
        val.remove(0,2);
    }

    qint32 n = val.toInt(&ok, base);

    if (ok)
        return n;
    else
        return defaultValue;
}
//==============================================================================
quint32 strToIntDef(const QString &str, quint32 defaultValue)
{
    bool ok=false;
    int base = 10;
    QString val = str.trimmed();

    if ((val.length() > 2) && (val.left(2).toLower() == "0x")) {
        base = 16;
        val.remove(0,2);
    }

    quint32 n = val.toUInt(&ok, base);

    if (ok)
        return n;
    else
        return defaultValue;
}
//==============================================================================
qint64 strToIntDef(const QString &str, qint64 defaultValue)
{
    bool ok=false;
    int base = 10;
    QString val = str.trimmed();

    if ((val.length() > 2) && (val.left(2).toLower() == "0x")) {
        base = 16;
        val.remove(0,2);
    }

    qint64 n = val.toLongLong(&ok, base);

    if (ok)
        return n;
    else
        return defaultValue;
}
//==============================================================================
quint64 strToIntDef(const QString &str, quint64 defaultValue)
{
    bool ok=false;
    int base = 10;
    QString val = str.trimmed();

    if ((val.length() > 2) && (val.left(2).toLower() == "0x")) {
        base = 16;
        val.remove(0,2);
    }

    quint64 n = val.toULongLong(&ok, base);

    if (ok)
        return n;
    else
        return defaultValue;
}
//==============================================================================
QString doubleToStr(qreal val, int precise, QLocale::NumberOption numberOptions)
{
    if(qIsNaN(val))
        return "NaN";

    if(qIsInf(val))
        return "Inf";

    QLocale c(QLocale::C);
    c.setNumberOptions( numberOptions );
    QString valStr = qIsFinite(val) ? c.toString( val, 'f', precise) : "";

    if(valStr.isNull())
        return "";

    bool ok;
    double d=strToDouble(valStr, &ok);
    Q_UNUSED(d)
    return  ok ? valStr : "";
}
//==============================================================================
qreal strToDouble(const QString &str, bool *ok)
{
    QLocale c(QLocale::C);
    bool err;
    double val = c.toDouble( str, &err );

    if(!err)
        val = 0;

    if(ok)
        *ok = err;

    return val;
}
//==============================================================================
QDateTime strToDateTime(const QString &str)
{
    QString dtStr = str.trimmed();
    QStringList lst = dtStr.split(' ', QString::SkipEmptyParts);

    if(lst.size() != 2)
        lst = dtStr.split('T', QString::SkipEmptyParts);

    if(lst.size() != 2)
        return QDateTime::fromMSecsSinceEpoch(-1);

    int y=0, m=0, d=0, h=0, n=0, s=0;

    if(dtStr.contains('-')) {
        QStringList dtLst = QString( lst.first() ).split('-', QString::SkipEmptyParts);
        if(dtLst.size() != 3) return QDateTime::fromMSecsSinceEpoch(-1);
        y = strToIntDef(dtLst.at(0), -1);
        m = strToIntDef(dtLst.at(1), -1);
        d = strToIntDef(dtLst.at(2), -1);
    }
    else if(dtStr.contains('.')) {
        QStringList dtLst = QString( lst.first() ).split('.', QString::SkipEmptyParts);
        if(dtLst.size() != 3) return QDateTime::fromMSecsSinceEpoch(-1);
        y = strToIntDef(dtLst.at(2), -1);
        m = strToIntDef(dtLst.at(1), -1);
        d = strToIntDef(dtLst.at(0), -1);
    }

    if(y>0 && y<1000)
        y += 2000;

    QStringList tmLst = QString( lst.last() ).split(':', QString::SkipEmptyParts);

    if(tmLst.size() < 2)
        return QDateTime::fromMSecsSinceEpoch(-1);

    h = strToIntDef(tmLst.at(0), -1);
    n = strToIntDef(tmLst.at(1), -1);

    if(tmLst.size() > 2)
        s = strToIntDef(tmLst.at(2), -1);

    return QDateTime( QDate(y, m, d), QTime(h, n, s) );
}

} // namespace convert //=======================================================


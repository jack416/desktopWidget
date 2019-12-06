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
#ifndef GRAPH_H
#define GRAPH_H

#include <QtCore>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QColor>
#include <QRgb>

namespace graph { //============================================================

bool drawImage(QPainter* painter, const QString &fileName, qreal x, qreal y, qreal width, qreal height);
bool drawImage(QPainter* painter, const QString &fileName, const QRectF &rectF);
bool drawImage(QPainter* painter, const QImage &image, qreal x, qreal y, qreal width, qreal height);
bool drawImage(QPainter* painter, const QImage &image, const QRectF &rectF);
bool drawRectangle(QPainter* painter, qreal x, qreal y, qreal width, qreal height,
                   const QColor &bgColor, const QColor &borderColor, qreal borderWidth,
                   qreal topRadius, qreal bottomRadius);
bool drawRectangle(QPainter* painter, const QRectF &rect,
                   const QColor &bgColor, const QColor &borderColor, qreal borderWidth,
                   qreal topRadius, qreal bottomRadius);
bool drawRectangle(QPainter* painter, qreal x, qreal y, qreal width, qreal height,
                   const QJsonArray &bgColor, const QJsonArray &borderColor, qreal borderWidth,
                   qreal topRadius, qreal bottomRadius);
bool drawRectangle(QPainter* painter, const QRectF &rect,
                   const QJsonArray &bgColor, const QJsonArray &borderColor, qreal borderWidth,
                   qreal topRadius, qreal bottomRadius);
bool drawCircle(QPainter* painter, qreal x, qreal y, qreal radius,
                const QColor &bgColor, const QColor &borderColor, qreal borderWidth );
bool drawCircle(QPainter* painter, qreal x, qreal y, qreal radius,
                const QJsonArray &bgColor, const QJsonArray &borderColor, qreal borderWidth );
bool drawCircle(QPainter* painter, const QPointF &centerPoint, qreal radius,
                const QColor &bgColor, const QColor &borderColor, qreal borderWidth );
bool drawCircle(QPainter* painter, const QPointF &centerPoint, qreal radius,
                const QJsonArray &bgColor, const QJsonArray &borderColor, qreal borderWidth );
bool drawCircle(QPainter* painter, const QPoint &centerPoint, qreal radius,
                const QJsonArray &bgColor, const QJsonArray &borderColor, qreal borderWidth );
bool drawCircle(QPainter* painter, const QPoint &centerPoint, qreal radius,
                const QColor &bgColor, const QColor &borderColor, qreal borderWidth );
bool drawText(QPainter* painter, qreal x, qreal y, const QString &text,
              const QString &fontFace, qreal fontSize, qreal fontWeight, const QColor &color,
              Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop, const QColor &shadowColor = QColor(0,0,0,0),
              qreal shadow_cx = 0, qreal shadow_cy = 0);
bool drawText(QPainter* painter, qreal x, qreal y, const QString &text,
              const QString &fontFace, qreal fontSize, qreal fontWeight, const QJsonArray &color,
              Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop, const QJsonArray &shadowColor = QJsonArray(),
              qreal shadow_cx = 0, qreal shadow_cy = 0);
bool drawText(QPainter* painter, QPointF pos, const QString &text,
              const QString &fontFace, qreal fontSize, qreal fontWeight, const QColor &color,
              Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop, const QColor &shadowColor = QColor(0,0,0,0),
              qreal shadow_cx = 0, qreal shadow_cy = 0);
bool drawText(QPainter* painter, QPointF pos, const QString &text,
              const QString &fontFace, qreal fontSize, qreal fontWeight, const QJsonArray &color,
              Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop, const QJsonArray &shadowColor = QJsonArray(),
              qreal shadow_cx = 0, qreal shadow_cy = 0);
QRectF textBoundingRect(QPainter* painter, const QString &text,
                        const QString &fontFace, qreal fontSize, qreal fontWeight);


QColor colorFromArray(const QJsonArray &arr);
QColor colorFromArray(const QByteArray &arr);
QColor colorFromArray(const QVector<quint8> &arr);

} // namespace graph //=========================================================
#endif // GRAPH_H

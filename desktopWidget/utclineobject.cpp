#include "Graph"
#include "utclineobject.h"
//==============================================================================

using namespace nayk;

//==============================================================================
UtcLineObject::UtcLineObject(Settings *settings)
    : m_settings {settings}
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);

    m_utcLine = m_settings->utcLine();
    qreal h = m_settings->screenGeometry().height() - m_settings->box().height - 30.0;
    qreal textHeight = m_settings->map().infoFont.size + 4;
    m_boundingRect.setRect( 0, 0, textHeight * 20, h);
}
//==============================================================================
UtcLineObject::~UtcLineObject()
{
    emit toLog(tr("UtcLineObject Destructor"), Log::LogDbg);
}
//==============================================================================
void UtcLineObject::utcLineChanged(const UtcLineStruct &utcLineStruct)
{
    m_utcLine = utcLineStruct;
    update();
}
//==============================================================================
QRectF UtcLineObject::boundingRect() const
{
    return m_boundingRect;
}
//==============================================================================
void UtcLineObject::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    qreal h = m_settings->screenGeometry().height() - m_settings->box().height - 30.0;
    qreal textHeight = m_settings->map().infoFont.size + 4;
    QPen linePen( QBrush( m_utcLine.line_color ), m_utcLine.line_width, Qt::DashLine);
    qreal x = m_boundingRect.width() / 2;
    qreal cy = m_settings->map().infoFont.size + 4;
    qreal y = h - (textHeight + cy) * 2;
    painter->setPen( linePen );
    painter->drawLine( QPointF(x, 0),
                       QPointF(x, y)
                       );
    y += cy;
    drawText(painter, x, y,
             QString(m_utcLine.date.toString("yyyy-MM-dd") + " 00:00"),
             m_settings->map().infoFont, Qt::AlignCenter);
    y += cy;
    drawText(painter, x, y,
             QString("lon = %1").arg(m_utcLine.lon),
             m_settings->map().infoFont, Qt::AlignCenter );
}
//==============================================================================
void UtcLineObject::drawText(QPainter *painter, qreal x, qreal y,
                             const QString &text, const FontStruct &font,
                             Qt::Alignment align, bool withShadow)
{
    graph::drawText(painter, x, y, text, font.font_face, font.size, font.weight,
                    font.color, align,
                    withShadow ? m_settings->shadow().color : QColor(0,0,0,0),
                    m_settings->shadow().cx, m_settings->shadow().cy );
}
//==============================================================================

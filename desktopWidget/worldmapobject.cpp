#include <QImage>
//
#include "Graph"
//
#include "worldmapobject.h"
//==============================================================================

using namespace nayk;

//==============================================================================
WorldMapObject::WorldMapObject(Settings *settings)
{
    setFlag(QGraphicsItem::ItemIgnoresTransformations);

    m_shadow = settings->shadow();
    m_comm = settings->common();
    m_map = settings->map();
    m_bg = settings->bg();
    m_miniCityVec = settings->miniCityVec();
    m_cityVec = settings->cityVec();
    m_curLoc = settings->currentLocation();

    m_boundingRect.setRect( 0, 0,
                            settings->screenGeometry().width(),
                            settings->screenGeometry().height());
    m_width = settings->screenGeometry().width();
    m_height = settings->screenGeometry().height() - settings->box().height;
}
//==============================================================================
WorldMapObject::~WorldMapObject()
{
    emit toLog(tr("WorldMapObject Destructor"), Log::LogDbg);
}
//==============================================================================
void WorldMapObject::currentLocationChanged(const CurrentLocationStruct &currentLocation)
{
    emit toLog(tr("WorldMapObject slot currentLocationChanged()"), Log::LogDbg);
    m_curLoc = currentLocation;
    update();
}
//==============================================================================
QRectF WorldMapObject::boundingRect() const
{
    return m_boundingRect;
}
//==============================================================================
void WorldMapObject::paint(QPainter *painter,
                           const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    drawBackground(painter);
    drawCities(painter);
    drawCurrentLocation(painter);
}
//==============================================================================
void WorldMapObject::drawText(QPainter *painter, qreal x, qreal y,
                              const QString &text, const FontStruct &font,
                              Qt::Alignment align, bool withShadow)
{
    graph::drawText(painter, x, y, text, font.font_face, font.size, font.weight,
                    font.color, align,
                    withShadow ? m_shadow.color : QColor(0,0,0,0),
                    m_shadow.cx, m_shadow.cy );
}
//==============================================================================
void WorldMapObject::drawBackground(QPainter *painter)
{
    if(m_bg.ok) graph::drawImage( painter, m_bg.img, m_bg.rect );
}
//==============================================================================
void WorldMapObject::drawCities(QPainter *painter)
{
    for(const auto &rec: m_miniCityVec) {

        if(rec.city != m_curLoc.city)
            graph::drawCircle(painter, rec.point, m_map.hide_caption_dot_radius,
                              m_map.hide_caption_dot_color, m_map.city_border_color,
                              m_map.city_dot_border );
    }

    for(const auto &rec: m_cityVec) {

        if(rec.city != m_curLoc.city) {
            graph::drawCircle(painter, rec.point, m_map.city_dot_radius,
                              m_map.city_dot_color, m_map.city_border_color,
                              m_map.city_dot_border);
            qreal x = rec.point.x() + (m_map.city_dot_radius + 4.0);
            qreal y = rec.point.y() - (m_map.city_dot_radius - 1.0);

            drawText(painter, x, y, rec.city, m_map.cityFont, Qt::AlignBottom);
        }
    }
}
//==============================================================================
void WorldMapObject::drawCurrentLocation(QPainter *painter)
{
    QPen linePen( QBrush( m_map.line_color ), m_map.line_width);

    qreal cy = 50.0;
    constexpr qreal cx = 50.0;

    painter->setPen( linePen );
    painter->drawLine( QPointF(m_curLoc.point.x(), cy),
                       QPointF(m_curLoc.point.x(), m_height - cy ) );
    painter->drawLine( QPointF(cx, m_curLoc.point.y()),
                       QPointF( m_width - cx, m_curLoc.point.y()) );

    qreal x = m_curLoc.point.x() + (m_map.current_dot_radius + 5.0);
    qreal y = m_curLoc.point.y() - (m_map.current_dot_radius - 1.0);

    drawText(painter, x, y, m_curLoc.city, m_map.currentFont, Qt::AlignBottom);

    x = m_width - 120.0;
    y = m_curLoc.point.y() + 14;
    cy = m_map.infoFont.size + 4;

    drawText(painter, x, y, m_curLoc.ip, m_map.infoFont);
    y += cy;
    drawText(painter, x, y, m_curLoc.country, m_map.infoFont);
    y += cy;
    drawText(painter, x, y, m_curLoc.city, m_map.infoFont);
    y += cy;
    drawText(painter, x, y, QString("lat = %1").arg(m_curLoc.lat), m_map.infoFont );
    y += cy;
    drawText(painter, x, y, QString("lon = %1").arg(m_curLoc.lon), m_map.infoFont );
}
//==============================================================================

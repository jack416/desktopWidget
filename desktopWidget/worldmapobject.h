#ifndef WORLDMAPOBJECT_H
#define WORLDMAPOBJECT_H

#include <QGraphicsObject>
//
#include "Log"
//
#include "common.h"
#include "settings.h"
//==============================================================================
class WorldMapObject : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit WorldMapObject(Settings *settings);
    virtual ~WorldMapObject();

signals:
    void toLog(const QString &text, nayk::Log::LogType logType = nayk::Log::LogInfo);

public slots:
    void currentLocationChanged(const CurrentLocationStruct &currentLocation);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal m_width;
    qreal m_height;
    QRectF m_boundingRect;
    ShadowStruct m_shadow;
    CommonStruct m_comm;
    MapStruct m_map;
    BgStruct m_bg;
    CurrentLocationStruct m_curLoc;
    QVector<CityStruct> m_miniCityVec;
    QVector<CityStruct> m_cityVec;

    void drawText(QPainter* painter, qreal x, qreal y, const QString &text, const FontStruct &font,
                          Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop, bool withShadow = true);
    void drawBackground(QPainter* painter);
    void drawCities(QPainter* painter);
    void drawCurrentLocation(QPainter* painter);
};
//==============================================================================
#endif // WORLDMAPOBJECT_H

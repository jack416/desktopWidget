#ifndef MONITOROBJECT_H
#define MONITOROBJECT_H

#include <QGraphicsObject>
#include <QTimer>
//
#include "Log"
//
#include "common.h"
#include "settings.h"
//==============================================================================
class MonitorObject : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit MonitorObject(Settings *settings);
    virtual ~MonitorObject();

signals:
    void toLog(const QString &text, nayk::Log::LogType logType = nayk::Log::LogInfo);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    bool m_busy {false};
    quint64 m_counter {0};
    QRectF m_boundingRect;
    QTimer m_timer;
    ShadowStruct m_shadow;
    BoxStruct m_box;
    GaugeStruct m_gauge;
    GraphStruct m_graph;
    BulletStruct m_bullet;
    QVector<MonitorStruct> m_monVec;

    void updateValues();
    void drawMonitor(QPainter* painter, const MonitorStruct &mon);
    void drawText(QPainter* painter, qreal x, qreal y, const QString &text, const FontStruct &font,
                          Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop, bool withShadow = true);

private slots:
    void on_timerTimeOut();

};
//==============================================================================
#endif // MONITOROBJECT_H

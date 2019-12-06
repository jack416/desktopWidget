#ifndef UTCLINEOBJECT_H
#define UTCLINEOBJECT_H

#include <QGraphicsObject>
//
#include "Log"
//
#include "common.h"
#include "settings.h"
//==============================================================================
class UtcLineObject : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit UtcLineObject(Settings *settings);
    virtual ~UtcLineObject();

signals:
    void toLog(const QString &text, nayk::Log::LogType logType = nayk::Log::LogInfo);

public slots:
    void utcLineChanged(const UtcLineStruct &utcLineStruct);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Settings *m_settings;
    QRectF m_boundingRect;
    UtcLineStruct m_utcLine;

    void drawText(QPainter* painter, qreal x, qreal y, const QString &text, const FontStruct &font,
                          Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop, bool withShadow = true);
};
//==============================================================================
#endif // UTCLINEOBJECT_H

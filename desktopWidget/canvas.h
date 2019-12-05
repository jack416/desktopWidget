#ifndef CANVAS_H
#define CANVAS_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsObject>
#include <QTimer>
#include <QMenu>
#include <QEvent>
#include "Log"
#include "settings.h"
#include "customscene.h"
//==============================================================================
class Canvas : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    virtual ~Canvas();

signals:
    void toLog(const QString &text, nayk::Log::LogType logType = nayk::Log::LogInfo);
    void quit();

private:
    nayk::Log *m_log {nullptr};
    Settings *m_settings {nullptr};
    CustomScene *m_scene {nullptr};
    QMenu m_menu;

    void setupMenu();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_settingsStartReading();
    void on_settingsFinishReading();
    void on_actionAboutTriggered();
    void on_actionOpenMapTriggered();
    void on_sceneRightClick(const QPoint &screenPos, const QPointF &scenePos);
    void on_currentLocationChanged(const CurrentLocationStruct &currentLocation);

};
//==============================================================================
#endif // CANVAS_H

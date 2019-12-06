#include <QApplication>
#include "customscene.h"
//==============================================================================

using namespace nayk;

//==============================================================================
CustomScene::CustomScene(QObject *parent)
    : QGraphicsScene(parent)
{

}
//==============================================================================
CustomScene::~CustomScene()
{

}
//==============================================================================
void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit toLog(tr("CustomScene slot mousePressEvent(), "
                  "scenePos x=%1, y=%2 screenPos x=%3, y=%4")
               .arg(event->scenePos().x())
               .arg(event->scenePos().y())
               .arg(event->screenPos().x())
               .arg(event->screenPos().y()),
               Log::LogDbg);
    if(event->button() == Qt::RightButton)
        emit rightButtonClick(event->screenPos());
}
//==============================================================================

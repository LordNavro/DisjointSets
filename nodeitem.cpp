#include "nodeitem.h"

NodeItem::NodeItem(QObject * parentObject, QGraphicsItem *parentItem) : QObject(parentObject), QGraphicsEllipseItem(parentItem){}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalNodeClicked(node);
    //QGraphicsEllipseItem::mouseReleaseEvent(event);
}

#include "nodeitem.h"

NodeItem::NodeItem(QObject * parentObject, QGraphicsItem *parentItem) : QObject(parentObject), QGraphicsEllipseItem(parentItem){}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsEllipseItem::mousePressEvent(event);
    emit signalNodeClicked(node);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsEllipseItem::paint(painter, option, widget);
    painter->drawText(boundingRect(), label, QTextOption(Qt::AlignCenter));
}

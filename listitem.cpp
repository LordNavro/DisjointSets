#include "listitem.h"


ListItem::ListItem(QObject * parentObject, QGraphicsItem *parentItem) : QObject(parentObject), QGraphicsRectItem(parentItem){}

void ListItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsEllipseItem::mousePressEvent(event);
    emit signalNodeClicked(node);
}

void ListItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);
    painter->drawText(boundingRect(), label, QTextOption(Qt::AlignCenter));
}

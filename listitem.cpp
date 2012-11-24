#include "listitem.h"


void ListItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit signalNodeClicked(this->node, this);
}

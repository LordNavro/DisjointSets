#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>
#include <QGraphicsItem>
#include "node.h"

class ListItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    Node *node;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalNodeClicked(Node *node, ListItem *listItem);
};

#endif // LISTITEM_H

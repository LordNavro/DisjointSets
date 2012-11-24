#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include "node.h"

class NodeItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    NodeItem(QObject *parentObject, QGraphicsItem *parentItem);

    Node *node;
    bool highlighted;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalNodeClicked(Node *node);
};

#endif // NODEITEM_H

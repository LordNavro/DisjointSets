#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include "node.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QInputDialog>

class NodeItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    NodeItem(QObject *parentObject, QGraphicsItem *parentItem);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString label;
    Node *node;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalNodeClicked(Node *node);
};

#endif // NODEITEM_H

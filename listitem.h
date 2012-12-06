#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>
#include <QGraphicsItem>
#include "node.h"
#include <QPainter>


class ListItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    ListItem(QObject *parentObject, QGraphicsItem *parentItem);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QString label;
    Node *node;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalNodeClicked(Node *node);
};

#endif // LISTITEM_H

#include "nodeitem.h"

NodeItem::NodeItem(QObject * parentObject, QGraphicsItem *parentItem) : QObject(parentObject), QGraphicsEllipseItem(parentItem){}

void NodeItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsEllipseItem::mousePressEvent(event);
    if(event->button() == Qt::RightButton)
    {
        bool ok;
        QString input = QInputDialog::getText(NULL, tr("Rename node"), tr("Enter new label:"),
                                              QLineEdit::Normal, this->node->label, &ok);
        if(ok && !input.isEmpty())
        {
            this->node->label = input;
            this->label = input;
            this->update();
        }
    }
    else
        emit signalNodeClicked(node);
}

void NodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsEllipseItem::paint(painter, option, widget);
    painter->drawText(boundingRect(), label, QTextOption(Qt::AlignCenter));
}

#include "listitem.h"


ListItem::ListItem(QObject * parentObject, QGraphicsItem *parentItem) : QObject(parentObject), QGraphicsRectItem(parentItem){}

void ListItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void ListItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter, option, widget);
    painter->drawText(boundingRect(), label, QTextOption(Qt::AlignCenter));
}

#ifndef DISJOINTSETSSCENE_H
#define DISJOINTSETSSCENE_H

#include <QGraphicsScene>
#include "node.h"
#include "nodeitem.h"
#include "listitem.h"

class DisjointSetsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    typedef enum {TREE, LIST} Representation;

    DisjointSetsScene(QObject *parent, QList<Node *> *forest, Representation representation, QPen nodePen, QBrush nodeBrush, QPen arrowPen);

    Representation representation;

    QList<Node *> *forest;
    QPen nodePen;
    QBrush nodeBrush;
    QPen arrowPen;

    void resetScene();
    void highlightNode(Node *node, QBrush brush, QPen pen);
    void highlightArrow(Node *from, Node *to, QPen pen);
    void unhighlightNode(Node *node);
    void unhighlightArrow(Node *from, Node *to);

    QList<Node *> highlightedNodes;
    QList<QPair<Node *, Node*> > highlightedArrows;

signals:
    void signalNodeClicked(Node *node);

protected:
    QPoint addNodeItemToScene(Node * node, QPoint startCoords);
};

#endif // DISJOINTSETSSCENE_H

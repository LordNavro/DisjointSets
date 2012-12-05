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

    DisjointSetsScene(QObject *parent, QList<Node *> *forest, Representation representation);

    Representation representation;

    QList<Node *> *forest;
    QPen nodePen;
    QBrush nodeBrush;
    QPen arrowPen;
    QPen nodeHighlightPen;
    QBrush nodeHighlightBrush;

    void resetScene();
    void addAsList();
    void addAsTree();
    void highlightNode(Node *node);
    void unhighlightNode(Node *node);

signals:
    void signalNodeClicked(Node *node);

protected:
    QPoint addNodeItemToScene(Node * node, QPoint startCoords);
    QPoint addListItemToScene(Node * node, QPoint startCoords);
};

#endif // DISJOINTSETSSCENE_H

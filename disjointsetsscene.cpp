#include "disjointsetsscene.h"

DisjointSetsScene::DisjointSetsScene(QObject *parent, QList<Node *> *forest, Representation representation, QPen nodePen, QBrush nodeBrush, QPen arrowPen)
    : QGraphicsScene(parent)
{
    this->forest = forest;
    this->nodePen = nodePen;
    this->nodeBrush = nodeBrush;
    this->arrowPen = arrowPen;
    this->representation = representation;
}

void DisjointSetsScene::resetScene(void)
{
    clear();
    QPoint coords(0,0);
    foreach(Node* tree, *forest)
    {
        coords = addNodeItemToScene(tree, coords);
        coords.setY(0);
    }
    update();
}

QPoint DisjointSetsScene::addNodeItemToScene(Node * node, QPoint startCoords)
{
    NodeItem *nodeItem = new NodeItem(0, 0);
    nodeItem->node = node;
    connect(nodeItem, SIGNAL(signalNodeClicked(Node*)), this, SIGNAL(signalNodeClicked(Node*)));

    nodeItem->setRect(startCoords.x(), startCoords.y(), 30, 30);
    nodeItem->setBrush(nodeBrush);
    nodeItem->setPen(nodePen);
    QPoint endCoords(startCoords);
    foreach(Node *child, node->children)
    {
        endCoords.setY(startCoords.y() + 60);
        addLine(startCoords.x() + 15, startCoords.y() + 15, endCoords.x() + 15, endCoords.y() + 15, arrowPen);
        endCoords = addNodeItemToScene(child, endCoords);
    }
    addItem(nodeItem);
    if(node->children.length() == 0)
        endCoords.setX(endCoords.x() + 40);
    return endCoords;
}

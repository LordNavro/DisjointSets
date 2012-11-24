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
    if(representation == LIST)
        addAsList();
    else
        addAsTree();
    update();
}

void DisjointSetsScene::addAsList()
{
    QPoint coords(0,0);
    foreach(Node* tree, *forest)
    {
        coords = addListItemToScene(tree, coords);
        coords.setX(0);
        coords.setY(coords.y() + 60);
    }
}

void DisjointSetsScene::addAsTree()
{
    QPoint coords(0,0);
    foreach(Node* tree, *forest)
    {
        coords = addNodeItemToScene(tree, coords);
        coords.setY(0);
    }
}

QPoint DisjointSetsScene::addNodeItemToScene(Node * node, QPoint startCoords)
{
    NodeItem *nodeItem = new NodeItem(this, NULL);
    nodeItem->node = node;
    connect(nodeItem, SIGNAL(signalNodeClicked(Node*)), this, SIGNAL(signalNodeClicked(Node*)));
    nodeItem->label = node->label;
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

QPoint DisjointSetsScene::addListItemToScene(Node *node, QPoint startCoords)
{
    ListItem *listItem = new ListItem(this, NULL);
    listItem->node = node;
    connect(listItem, SIGNAL(signalNodeClicked(Node*)), this, SIGNAL(signalNodeClicked(Node*)));
    listItem->label = node->label;
    listItem->setRect(startCoords.x(), startCoords.y(), 30, 30);
    listItem->setBrush(nodeBrush);
    listItem->setPen(nodePen);
    foreach(Node *child, node->children)
    {
        addLine(startCoords.x() + 30, startCoords.y() + 15, startCoords.x() + 60, startCoords.y() + 15, arrowPen);
        startCoords.setX(startCoords.x() + 60);
        startCoords = addListItemToScene(child, startCoords);
    }
    addItem(listItem);
    return startCoords;
}

#include "disjointsetsscene.h"

DisjointSetsScene::DisjointSetsScene(QObject *parent, QList<Node *> *forest, Representation representation)
    : QGraphicsScene(parent)
{
    this->forest = forest;
    this->nodePen = QPen(Qt::black);
    this->nodeBrush = QBrush(Qt::green);
    this->arrowPen = QPen(Qt::black);
    this->nodeHighlightPen = QPen(Qt::yellow);
    this->nodeHighlightBrush = QBrush(Qt::red);
    this->representation = representation;
}

void DisjointSetsScene::resetScene(void)
{
    clear();
    //simulate top and left padding
    addLine(-20,-20,0,0,QPen(Qt::white));
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

void DisjointSetsScene::highlightNode(Node *node)
{
    foreach(QGraphicsItem *item, this->items())
    {
        if(NodeItem *i = qgraphicsitem_cast<NodeItem *>(item))
        {
            if(i->node == node)
            {
                i->setBrush(nodeHighlightBrush);
                i->setPen(nodeHighlightPen);
                i->update();
            }
        }
        if(ListItem *i = qgraphicsitem_cast<ListItem *>(item))
        {
            if(i->node == node)
            {
                i->setBrush(nodeHighlightBrush);
                i->setPen(nodeHighlightPen);
                i->update();
            }
        }
    }
}

void DisjointSetsScene::unhighlightNode(Node *node)
{
    foreach(QGraphicsItem *item, this->items())
    {
        if(NodeItem *i = qgraphicsitem_cast<NodeItem *>(item))
        {
            if(i->node == node)
            {
                i->setBrush(nodeBrush);
                i->setPen(nodePen);
                i->update();
            }
        }
        if(ListItem *i = qgraphicsitem_cast<ListItem *>(item))
        {
            if(i->node == node)
            {
                i->setBrush(nodeBrush);
                i->setPen(nodePen);
                i->update();
            }
        }
    }
}

ListItem *DisjointSetsScene::findItem(Node *node)
{
    foreach(QGraphicsItem *item, this->items())
    {
        if(ListItem *i = qgraphicsitem_cast<ListItem *>(item))
        {
            if(i->node == node)
            {
                return i;
            }
        }
    }
    return NULL;
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
        addLine(startCoords.x() + 15, startCoords.y() + 15, endCoords.x() + 15, endCoords.y(), arrowPen);
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

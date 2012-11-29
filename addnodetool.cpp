#include "addnodetool.h"


AddNodeTool::AddNodeTool(DisjointSetsScene *scene, QObject *parent) : Tool(scene, parent){}

void AddNodeTool::selectTool()
{

}

void AddNodeTool::deselectTool()
{

}

void AddNodeTool::nodeClicked(Node *node)
{
    static int counter;
    Node *newNode = new Node(node, ("c") + QString::number(counter++));
    if(scene->representation == DisjointSetsScene::TREE)
        node->children.append(newNode);
    else
        node->children.prepend(newNode);
    scene->resetScene();
}

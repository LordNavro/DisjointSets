#include "deletenodetool.h"


DeleteNodeTool::DeleteNodeTool(DisjointSetsScene *scene) : Tool(scene){}

void DeleteNodeTool::selectTool()
{

}

void DeleteNodeTool::deselectTool()
{

}

void DeleteNodeTool::nodeClicked(Node *node)
{
    if(node->parent != NULL)
        node->parent->children.removeAt(node->parent->children.indexOf(node));
    else
        scene->forest->removeAt(scene->forest->indexOf(node));
    deleteNode(node);
    scene->resetScene();
}

void DeleteNodeTool::deleteNode(Node *node)
{
    foreach(Node * child, node->children)
        deleteNode(child);
    delete node;
}

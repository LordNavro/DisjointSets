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
        deleteNode(node);
    else
        deleteRootNode(node);
    scene->resetScene();
}

void DeleteNodeTool::deleteRootNode(Node *node)
{
    if(!node->children.length())
    {
        scene->forest->removeAt(scene->forest->indexOf(node));
        delete node;
        return;
    }
    Node *newRoot = node->children.first();
    node->children.removeFirst();
    newRoot->parent = NULL;
    scene->forest->replace(scene->forest->indexOf(node), newRoot);
    foreach(Node *child, node->children)
        child->parent = newRoot;
    newRoot->children.append(node->children);
    delete node;
}

void DeleteNodeTool::deleteNode(Node *node)
{
    if(!node->children.length())
    {
        node->parent->children.removeAt(node->parent->children.indexOf(node));
        delete node;
        return;
    }
    Node *newNode = node->children.first();
    node->children.removeFirst();
    newNode->parent = node->parent;
    node->parent->children.replace(node->parent->children.indexOf(node), newNode);
    newNode->children.append(node->children);
    foreach(Node *child, node->children)
        child->parent = newNode;
    delete node;
}

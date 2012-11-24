#include "addnodetool.h"


AddNodeTool::AddNodeTool(DisjointSetsScene *scene) : Tool(scene){}

void AddNodeTool::selectTool()
{

}

void AddNodeTool::deselectTool()
{

}

void AddNodeTool::nodeClicked(Node *node)
{
    Node *newNode = new Node(node, "child");
    node->children.append(newNode);
    scene->resetScene();
}

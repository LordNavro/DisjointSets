#include "uniontool.h"


UnionTool::UnionTool(DisjointSetsScene *scene, QObject *parent) : Tool(scene, parent){}

void UnionTool::selectTool()
{
    firstNode = NULL;
}

void UnionTool::deselectTool()
{
    if(firstNode != NULL)
        scene->unhighlightNode(firstNode);
}

void UnionTool::nodeClicked(Node *node)
{
    if(firstNode == NULL)
    {
        firstNode = node;
        scene->highlightNode(node);
    }
    else if(firstNode == node)
    {
        scene->unhighlightNode(firstNode);
        firstNode = NULL;
    }
    else
    {
        simulate(this->firstNode, node);
        firstNode = NULL;
        scene->unhighlightNode(firstNode);
    }
}

void UnionTool::simulate(Node *n1, Node *n2)
{
    Simulation *simulation = new Simulation();
    DisjointSetsScene *s =  new DisjointSetsScene(NULL, scene->forest, scene->representation);
    s->resetScene();
    s->highlightNode(n1);
    s->highlightNode(n2);
    while(n1->parent != NULL)
        n1 = n1->parent;
    while(n2->parent != NULL)
        n2 = n2->parent;
    simulation->scenes.append(s);

    s =  new DisjointSetsScene(NULL, scene->forest, scene->representation);
    s->resetScene();
    s->highlightNode(n1);
    s->highlightNode(n2);
    simulation->scenes.append(s);
    if(n1 != n2)
    {
        if(optimize)
        {
            if(scene->representation == DisjointSetsScene::TREE)
            {
                //check heights and possibly swap n1, n2 so that n1 is shorter then n2
            }
            else
            {
                //check lengths and possibly swap n1, n2 so that n1 is shorter then n2
            }

        }
        if(scene->representation == DisjointSetsScene::TREE)
            simulateTree(s, n1, n2);
        else
            simulateList(s, n1, n2);

    }
    simulation->currentScene = simulation->scenes.begin();
    emit signalSimulate(simulation);
}

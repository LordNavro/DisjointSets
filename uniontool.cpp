#include "uniontool.h"
#include <stdio.h>

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

    //the node pointers we have point into the old forest
    simulation->finalForest = this->scene->forest;
    scene->forest = Utils::copyForest(simulation->finalForest);

    if(n1 != n2)
    {
        if(optimize)
        {
            if(scene->representation == DisjointSetsScene::TREE)
            {
                //check heights and possibly swap n1, n2 so that n1 is shorter then n2
                if(Utils::treeHeight(n1) < Utils::treeHeight(n2))
                {
                    Node *temp = n1;
                    n1 = n2;
                    n2 = temp;
                }
            }
            else
            {
                //check lengths and possibly swap n1, n2 so that n1 is shorter then n2
                if(Utils::listLength(n1) < Utils::listLength(n2))
                {
                    Node *temp = n1;
                    n1 = n2;
                    n2 = temp;
                }
            }

        }

        simulation->finalForest->removeAt(simulation->finalForest->indexOf(n2));
        n1->children.append(n2);
        n2->parent = n1;

        if(scene->representation == DisjointSetsScene::TREE)
            simulateTree(simulation, n1, n2);
        else
            simulateList(simulation, n1, n2);

    }

    simulation->currentScene = simulation->scenes.begin();
    emit signalSimulate(simulation);
}

void UnionTool::simulateTree(Simulation *simulation, Node *n1, Node *n2)
{
    DisjointSetsScene *s = new DisjointSetsScene(NULL, simulation->finalForest, DisjointSetsScene::TREE);
    s->resetScene();
    s->highlightNode(n1);
    s->highlightNode(n2);
    simulation->scenes.append(s);
}

void UnionTool::simulateList(Simulation *simulation, Node *n1, Node *n2)
{

    QList<Node *> nodesToReconnect = Utils::treeToList(n2);

    foreach(Node *n, nodesToReconnect)
    {
        DisjointSetsScene *s = new DisjointSetsScene(NULL, simulation->finalForest, DisjointSetsScene::LIST);
        s->resetScene();
        s->highlightNode(n);
        s->highlightNode(n1);
        ListItem *root = s->findItem(n1);
        ListItem *oldRoot = s->findItem(n2);

        //items already reconnected to new root
        foreach(Node *connected, nodesToReconnect)
        {
            ListItem *c = s->findItem(connected);
            s->addLine(c->boundingRect().left() + 15, c->boundingRect().top() + 30, c->boundingRect().left() + 15, c->boundingRect().top() + 40);
            if(connected == n)
            {
                s->addLine(root->boundingRect().left() + 15, root->boundingRect().top() + 30, root->boundingRect().left() + 15, root->boundingRect().top() + 40);
                s->addLine(root->boundingRect().left() + 15, root->boundingRect().top() + 40, c->boundingRect().left() + 15, c->boundingRect().top() + 40);
                break;
            }
        }

        //items still pointing to old root
        bool start = false;
        foreach(Node *unconnected, nodesToReconnect)
        {
            if(!start)
            {
                if(unconnected == n)
                    start = true;
                continue;
            }
            ListItem *c = s->findItem(unconnected);
            s->addLine(c->boundingRect().left() + 15, c->boundingRect().top(), c->boundingRect().left() + 15, c->boundingRect().top() - 10);
            if(unconnected == nodesToReconnect.last())
            {
                s->addLine(oldRoot->boundingRect().left() + 15, oldRoot->boundingRect().top(), oldRoot->boundingRect().left() + 15, oldRoot->boundingRect().top() - 10);
                s->addLine(oldRoot->boundingRect().left() + 15, oldRoot->boundingRect().top() - 10, c->boundingRect().left() + 15, c->boundingRect().top() - 10);
                break;
            }
        }

        simulation->scenes.append(s);
    }
}

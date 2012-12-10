#include "findsettool.h"


FindSetTool::FindSetTool(DisjointSetsScene *scene, QObject *parent) : Tool(scene, parent){}

void FindSetTool::selectTool()
{

}

void FindSetTool::deselectTool()
{

}

void FindSetTool::nodeClicked(Node *node)
{
    if(this->scene->representation == DisjointSetsScene::TREE)
        this->treeMode(node);
    else
        this->listMode(node);
}

void FindSetTool::treeMode(Node *node)
{
    if(this->optimize)
        this->treeModeOptimized(node);
    else
        this->treeModeUnoptimized(node);
}


void FindSetTool::treeModeUnoptimized(Node *node)
{

    Simulation *simulation = new Simulation();
    simulation->finalForest = Utils::copyForest(this->scene->forest);

    do{
        DisjointSetsScene *s = new DisjointSetsScene(scene, scene->forest, DisjointSetsScene::TREE);
        s->resetScene();
        s->highlightNode(node);
        s->label = "Walk to the root";
        simulation->scenes.append(s);
        node = node->parent;
    }while(node != NULL);

    simulation->currentScene = simulation->scenes.begin();
    emit signalSimulate(simulation);
}


void FindSetTool::treeModeOptimized(Node *node)
{
    Simulation *simulation = new Simulation();
    QList<Node *> path;

    Node *root = NULL;
    do{
        root = node;
        path.append(node);
        DisjointSetsScene *s = new DisjointSetsScene(scene, scene->forest, DisjointSetsScene::TREE);
        s->resetScene();
        s->label = "Walk to the root,\n remember path";
        foreach(Node *n, path)
            s->highlightNode(n);
        simulation->scenes.append(s);
        node = node->parent;
    }while(node != NULL);

    //the node pointers we have point into the old forest
    QList<Node *> *newForest = this->scene->forest;
    scene->forest = Utils::copyForest(newForest);

    foreach(Node *pathItem, path)
    {
        if(pathItem->parent == NULL || pathItem->parent == root)
               continue;
        pathItem->parent->children.removeAt(pathItem->parent->children.indexOf(pathItem));
        pathItem->parent = root;
        root->children.append(pathItem);
    }

    DisjointSetsScene *s = new DisjointSetsScene(scene, newForest, DisjointSetsScene::TREE);
    s->resetScene();
    s->label = "Finally, change all nodes\nto point to root";
    foreach(Node *n, path)
        s->highlightNode(n);
    simulation->scenes.append(s);

    simulation->finalForest = newForest;
    simulation->currentScene = simulation->scenes.begin();
    emit signalSimulate(simulation);
}


void FindSetTool::listMode(Node *node)
{

    Simulation *simulation = new Simulation();
    simulation->finalForest = Utils::copyForest(this->scene->forest);

    DisjointSetsScene *s1 = new DisjointSetsScene(scene, scene->forest, DisjointSetsScene::LIST);
    s1->resetScene();
    s1->highlightNode(node);
    simulation->scenes.append(s1);

    if(node->parent != NULL)
    {
        s1->label = "See the parent for " + node->label;
        DisjointSetsScene *s2 = new DisjointSetsScene(scene, scene->forest, DisjointSetsScene::LIST);
        s2->resetScene();
        ListItem * nodeItem = s2->findItem(node);
        s2->highlightNode(node);
        while(node->parent != NULL)
            node = node->parent;
        ListItem * rootItem = s2->findItem(node);

        s2->addLine(rootItem->boundingRect().left() + 15, rootItem->boundingRect().top() + 30, rootItem->boundingRect().left() + 15, rootItem->boundingRect().top() + 40);
        s2->addLine(nodeItem->boundingRect().left() + 15, nodeItem->boundingRect().top() + 30, nodeItem->boundingRect().left() + 15, nodeItem->boundingRect().top() + 40);
        s2->addLine(rootItem->boundingRect().left() + 15, rootItem->boundingRect().top() + 40, nodeItem->boundingRect().left() + 15, nodeItem->boundingRect().top() + 40);

        s2->highlightNode(node);
        s2->label = "The root pointer goes \n straight to " + node->label;
        simulation->scenes.append(s2);
    }
    else
        s1->label = node->label + " is a root node";


    simulation->currentScene = simulation->scenes.begin();
    emit signalSimulate(simulation);
}

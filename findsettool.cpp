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
    Simulation *simulation = new Simulation();
    simulation->finalForest = new QList<Node *>;
    DisjointSetsScene *s1 = new DisjointSetsScene(NULL, NULL, DisjointSetsScene::TREE, QPen(), QBrush(), QPen());
    DisjointSetsScene *s2 = new DisjointSetsScene(NULL, NULL, DisjointSetsScene::TREE, QPen(), QBrush(), QPen());
    DisjointSetsScene *s3 = new DisjointSetsScene(NULL, NULL, DisjointSetsScene::TREE, QPen(), QBrush(), QPen());
    s1->addText("SCENA 1");
    s2->addText("SCENA 2");
    s3->addText("SCENA 3");
    simulation->scenes.append(s1);
    simulation->scenes.append(s2);
    simulation->scenes.append(s3);
    simulation->currentScene = simulation->scenes.begin();
    emit signalSimulate(simulation);
}

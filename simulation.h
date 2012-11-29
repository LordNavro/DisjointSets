#ifndef SIMULATION_H
#define SIMULATION_H

#include <QList>
#include "disjointsetsscene.h"
#include "node.h"

class Simulation
{
public:
    Simulation();
    ~Simulation();

    QList<DisjointSetsScene *> scenes;
    QList<Node *> *finalForest;
    QList<DisjointSetsScene *>::iterator currentScene;
};

#endif // SIMULATION_H

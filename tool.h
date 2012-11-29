#ifndef TOOL_H
#define TOOL_H

#include "node.h"
#include "nodeitem.h"
#include "listitem.h"
#include "disjointsetsscene.h"
#include "simulation.h"
#include <QObject>

class Tool: public QObject
{
    Q_OBJECT
public:
    Tool(DisjointSetsScene *scene, QObject *parent = NULL);

    DisjointSetsScene *scene;

    virtual void nodeClicked(Node *node) = 0;
    virtual void selectTool(void) = 0;
    virtual void deselectTool(void) = 0;

signals:
    void signalSimulate(Simulation *);
};

#endif // TOOL_H

#ifndef TOOL_H
#define TOOL_H

#include "node.h"
#include "nodeitem.h"
#include "listitem.h"
#include "disjointsetsscene.h"

class Tool
{
public:
    Tool(DisjointSetsScene *scene);

    DisjointSetsScene *scene;

    virtual void nodeClicked(Node *node) = 0;
    virtual void selectTool(void) = 0;
    virtual void deselectTool(void) = 0;
};

#endif // TOOL_H

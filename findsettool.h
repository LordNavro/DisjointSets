#ifndef FINDSETTOOL_H
#define FINDSETTOOL_H

#include "tool.h"

class FindSetTool : public Tool
{
public:
    FindSetTool(DisjointSetsScene *scene, QObject *parent = NULL);

    void nodeClicked(Node *node);
    void selectTool();
    void deselectTool();
};

#endif // FINDSETTOOL_H

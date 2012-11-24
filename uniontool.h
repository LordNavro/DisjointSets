#ifndef UNIONTOOL_H
#define UNIONTOOL_H

#include "tool.h"

class UnionTool: public Tool
{
public:
    UnionTool(DisjointSetsScene *scene);

    void nodeClicked(Node *node);
    void selectTool();
    void deselectTool();
};

#endif // UNIONTOOL_H

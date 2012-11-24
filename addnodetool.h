#ifndef ADDNODETOOL_H
#define ADDNODETOOL_H

#include "tool.h"

class AddNodeTool : public Tool
{
public:
    AddNodeTool(DisjointSetsScene *scene);

    void nodeClicked(Node *node);
    void selectTool();
    void deselectTool();
};

#endif // ADDNODETOOL_H

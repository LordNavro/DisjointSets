#ifndef DELETENODETOOL_H
#define DELETENODETOOL_H

#include "tool.h"
#include <iostream>

class DeleteNodeTool : public Tool
{
public:
    DeleteNodeTool(DisjointSetsScene *scene);

    void nodeClicked(Node *node);
    void selectTool();
    void deselectTool();
    void deleteRootNode(Node *node);
    void deleteNode(Node *node);
};

#endif // DELETENODETOOL_H

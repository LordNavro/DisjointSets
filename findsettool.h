#ifndef FINDSETTOOL_H
#define FINDSETTOOL_H

#include "tool.h"
#include "utils.h"

class FindSetTool : public Tool
{
public:
    FindSetTool(DisjointSetsScene *scene, QObject *parent = NULL);
    bool optimize;

    void nodeClicked(Node *node);
    void selectTool();
    void deselectTool();

    void treeMode(Node *node);
    void treeModeUnoptimized(Node *node);
    void treeModeOptimized(Node *node);
    void listMode(Node *node);
};

#endif // FINDSETTOOL_H

#ifndef UNIONTOOL_H
#define UNIONTOOL_H

#include "tool.h"

class UnionTool: public Tool
{
public:
    UnionTool(DisjointSetsScene *scene, QObject *parent = NULL);
    bool optimize;
    Node *firstNode;

    void nodeClicked(Node *node);
    void selectTool();
    void deselectTool();
    void simulate(Node *n1, Node *n2);

    void simulateTree(Simulaion *s, Node *n1, Node *n2);
    void simulateList(Simulaion *s, Node *n1, Node *n2);
};

#endif // UNIONTOOL_H

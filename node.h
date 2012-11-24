#ifndef NODE_H
#define NODE_H
#include <QString>
#include <QList>

class Node
{
public:
    Node(Node *p = NULL, QString l = "");
    Node *parent;

    QString label;
    QList<Node *> children;


};

#endif // NODE_H

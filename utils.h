#ifndef UTILS_H
#define UTILS_H
#include <QList>
#include "node.h"
#include <QtXml/QDomDocument>

class Utils
{
public:
    static Node * copyTree(Node *tree, Node *parent = NULL);
    static void deleteTree(Node *tree);

    static QList<Node *> * copyForest(QList<Node *> *forest);
    static void deleteForest(QList<Node *> *forest);

    static QDomElement treeToXml(Node * tree, QDomDocument *xml);
    static Node * xmlToTree(QDomElement elem, Node *parent = NULL);

    static QDomDocument forestToXml(QList<Node *>forest);
    static QList<Node *> xmlToForest(QDomDocument xml);

private:
    Utils();
};

#endif // UTILS_H

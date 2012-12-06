#include "utils.h"

Utils::Utils()
{
    throw("Constructing utils is invalid");
}


Node *Utils::copyTree(Node *tree, Node *parent)
{
    Node *newNode = new Node(parent, tree->label);
    foreach(Node *child, tree->children)
        newNode->children.append(copyTree(child, newNode));
    return newNode;
}

void Utils::deleteTree(Node *tree)
{
    foreach(Node *child, tree->children)
        deleteTree(child);
    delete(tree);
}

QList<Node *> * Utils::copyForest(QList<Node *> *forest)
{
    QList<Node *> *newForest = new QList<Node *>;
    foreach(Node *tree, *forest)
        newForest->append(copyTree(tree));
    return newForest;
}

void Utils::deleteForest(QList<Node *> *forest)
{
    foreach(Node *tree, *forest)
        deleteTree(tree);
}

QDomElement Utils::treeToXml(Node *tree, QDomDocument *xml)
{
    QDomElement elem = xml->createElement("node");
    elem.setAttribute("label", tree->label);
    foreach(Node *child, tree->children)
        elem.appendChild(treeToXml(child, xml));
    return elem;
}

Node * Utils::xmlToTree(QDomElement elem, Node *parent)
{
    //fixme -> check element name is "node"?
    Node *node = new Node(parent, elem.attribute("label", ""));
    for(int i = 0; i < elem.childNodes().size(); i++)
        node->children.append(xmlToTree(elem.childNodes().at(i).toElement(), node));
    return node;
}

QDomDocument Utils::forestToXml(QList<Node *>forest)
{
    QDomDocument xml("DisjointSetsForest");
    QDomElement root = xml.createElement("forest");
    xml.appendChild(root);
    foreach(Node *tree, forest)
        root.appendChild(treeToXml(tree, &xml));
    return xml;
}

QList<Node *> Utils::xmlToForest(QDomDocument xml)
{
    //fixme -> check element name is "forest"?
    QList<Node *>forest;
    for(int i = 0; i < xml.childNodes().size(); i++)
        forest.append(xmlToTree(xml.childNodes().at(i).toElement()));
    return forest;
}

int Utils::treeHeight(Node *root)
{
    int height = 0;
    foreach(Node *child, root->children)
    {
        int ch = Utils::treeHeight(child);
        if(ch > height)
            height = ch;
    }
    return height + 1;
}

int Utils::listLength(Node *root)
{
    int length = 0;

    foreach(Node *child, root->children)
    {
        length += Utils::listLength(child);
    }
    return length + 1;
}

QList<Node *> Utils::treeToList(Node *node)
{
    QList<Node *> list;
    list.append(node);
    foreach(Node * child, node->children)
        list.append(treeToList(child));
    return list;
}



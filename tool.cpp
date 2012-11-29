#include "tool.h"

Tool::Tool(DisjointSetsScene *scene, QObject *parent) : QObject(parent)
{
    this->scene = scene;
}

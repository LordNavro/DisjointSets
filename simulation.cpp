#include "simulation.h"

Simulation::Simulation() : finalForest()
{

}

Simulation::~Simulation()
{
    delete this->finalForest;
}

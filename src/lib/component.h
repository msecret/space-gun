
#ifndef _h_Component
#define _h_Component

#include "positioning.h"

class Entity;

class Component
{
  public:
    virtual void receive(int message) = 0;
    virtual void update(Entity* entity, int dt) = 0;
};

#endif

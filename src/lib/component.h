
#ifndef _h_Component
#define _h_Component

#include "positioning.h"

class Entity;

class Component
{
  public:
    virtual void init(Entity* entity, Vector2d v) = 0;
    virtual void receive(int message) = 0;
    virtual void update(Entity* entity, int dt) = 0;
};

#endif


#ifndef _h_Component
#define _h_Component

#include "units.h"

namespace aronnax {

class Entity;

class Component
{
  public:
    virtual void update(Entity &entity, const int dt) = 0;
};

}

#endif

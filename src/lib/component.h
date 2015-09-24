
#ifndef _h_Component
#define _h_Component

#include <cstdint>
#include <vector>

#include "units.h"

namespace aronnax {

class Entity;

class Component
{
  public:
    virtual void update(Entity &entity, const uint32_t dt) {};
    virtual void render(Entity &entity) {};
};

typedef std::vector<Component> Components;

}

#endif

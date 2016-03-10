
#include <string>

#include "c_universal.h"
#include "s_universe.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;
  using aronnax::Entities;

  void Universe::update(const uint32_t dt, Entities& entities)
  {
    auto oneE = entities.at(0);
    updateWorld(dt, *oneE);
  }

  void Universe::updateWorld(const uint32_t dt, Entity& entity)
  {
    float timeStep = 0.1;
    int velocityIterations = 8;
    int positionIterations = 2;

    auto u = entity.getComponent<Universal>(COMPONENT_TYPE_UNIVERSAL);
    auto world = u->getWorld();

    world->Step(timeStep, velocityIterations, positionIterations);
  }

  const string& Universe::getType()
  {
    return COMPONENT_TYPE_UNIVERSAL;
  }
}

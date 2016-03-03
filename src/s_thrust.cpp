
#include <algorithm>

#include "lib/units.h"
#include "c_thrustable.h"
#include "c_moveable.h"
#include "s_thrust.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_THRUSTABLE;

  void Thrust::init(aronnax::Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
    }
  }

  void Thrust::onAddEntity(aronnax::Entity& entity)
  {
    bindEntity(entity);
  }

  void Thrust::bindEntity(aronnax::Entity& entity)
  {
    entity.on(aronnax::EV_USER_MOVEMENT,
        [&](aronnax::EvUserMovement* ev) {
      handleKeys(*ev, entity);
    });
  }

  void Thrust::handleKeys(aronnax::EvUserMovement& ev,
      aronnax::Entity& entity)
  {
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto thrustable = entity.getComponent<Thrustable>(
        COMPONENT_TYPE_THRUSTABLE);
    auto thrustFactor = thrustable->getFactor();

    aronnax::Vector2d curr = moveable->getVel();
    aronnax::Vector2d mod = ev.getDirection();
    // mod *= thrustFactor;
    mod.x *= thrustFactor;
    mod.y *= thrustFactor;
    aronnax::Vector2d newV = mod + curr;

    moveable->setVel(newV);
  }

  const string& Thrust::getType()
  {
    return COMPONENT_TYPE_THRUSTABLE;
  }

}

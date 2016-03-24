
#include <algorithm>
#include <iostream>

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
      handleMovementKey(*ev, entity);
      cout << "ev-user_move x:" << ev->getDirection().x
          << " y:" << ev->getDirection().y << endl;
    });
    entity.on(aronnax::EV_USER_ROTATION,
        [&](aronnax::EvUserRotation* ev) {
      handleRotationKey(*ev, entity);
      cout << "ev-user_rotation " << ev->getDirection() << endl;
    });
  }

  void Thrust::handleMovementKey(aronnax::EvUserMovement& ev,
      aronnax::Entity& entity)
  {
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto thrustable = entity.getComponent<Thrustable>(
        COMPONENT_TYPE_THRUSTABLE);
    auto thrustFactor = thrustable->getFactor();

    Vector2d curr = moveable->getVel();
    Vector2d mod = ev.getDirection();
    // mod *= thrustFactor;
    mod.x *= thrustFactor;
    mod.y *= thrustFactor;
    Vector2d newV = mod + curr;

    moveable->applyForce(newV);
  }

  void Thrust::handleRotationKey(aronnax::EvUserRotation& ev,
      aronnax::Entity& entity)
  {
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto thrustable = entity.getComponent<Thrustable>(
        COMPONENT_TYPE_THRUSTABLE);
    auto thrustFactor = thrustable->getFactor();

    auto torque = ev.getDirection() * thrustFactor;

    moveable->applyTorque(torque);
  }

  const string& Thrust::getType()
  {
    return COMPONENT_TYPE_THRUSTABLE;
  }

}


#include <algorithm>
#include <cmath>
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
      //cout << "ev-user_move x:" << ev->getDirection().x
      //    << " y:" << ev->getDirection().y << endl;
    });
    entity.on(aronnax::EV_USER_ROTATION,
        [&](aronnax::EvUserRotation* ev) {
      handleRotationKey(*ev, entity);
      //cout << "ev-user_rotation " << ev->getDirection() << endl;
    });
  }

  void Thrust::handleMovementKey(aronnax::EvUserMovement& ev,
      aronnax::Entity& entity)
  {
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto thrustable = entity.getComponent<Thrustable>(
        COMPONENT_TYPE_THRUSTABLE);
    auto thrustFactor = thrustable->getFactor();
    auto direction = ev.getDirection();

    auto angle = moveable->getAngle();

    auto force = getForce(direction, angle);
    force *= thrustFactor;
    if (direction == Vector2d(1, 1)) {
      force *= 3;
    }

    moveable->applyForce(force);
  }

  void Thrust::handleRotationKey(aronnax::EvUserRotation& ev,
      aronnax::Entity& entity)
  {
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto thrustable = entity.getComponent<Thrustable>(
        COMPONENT_TYPE_THRUSTABLE);
    auto thrustFactor = thrustable->getFactor();

    auto torque = ev.getDirection() * thrustFactor * 9;

    moveable->applyTorque(torque);
  }

  Vector2d Thrust::getForce(Vector2d direction, float angle)
  {
    Vector2d right = { 1, 0 };
    Vector2d left = { -1, 0 };
    Vector2d force;
    Vector2d currForce;

    currForce.x = cos(angle);
    currForce.y = sin(angle);

    if (direction == right || direction == left) {
      float ninety = 1.5708f * direction.x;
      auto cs = cos(ninety);
      auto sn = sin(ninety);
      force.x = currForce.x * cs - currForce.y * sn;
      force.y = currForce.x * sn + currForce.y * cs;
    } else {
      force = currForce;
      force.x *= direction.x;
      force.y *= direction.y;
    }

    return force;
  }

  const string& Thrust::getType()
  {
    return COMPONENT_TYPE_THRUSTABLE;
  }

}

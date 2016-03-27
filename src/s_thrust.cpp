
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

  Vector2d normalize(Vector2d v){
    Vector2d vector;
    float length = v.Length();

    if(length != 0){
        vector.x = v.x/length;
        vector.y = v.y/length;
    }

    return vector;
  }

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
    Vector2d right = { 1, 0 };
    Vector2d left = { -1, 0 };
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto thrustable = entity.getComponent<Thrustable>(
        COMPONENT_TYPE_THRUSTABLE);
    auto thrustFactor = thrustable->getFactor();
    auto direction = ev.getDirection();

    Vector2d force;
    auto angle = moveable->getAngle();
    if (direction == right || direction == left) {
      float ninety = 1.5708f * direction.x;
      Vector2d currForce;
      currForce.x = cos(angle);
      currForce.y = sin(angle);
      auto cs = cos(ninety);
      auto sn = sin(ninety);
      force.x = currForce.x * cs - currForce.y * sn;
      force.y = currForce.x * sn + currForce.y * cs;
    } else {
      force.x = cos(angle);
      force.y = sin(angle);
      force.x *= direction.x;
      force.y *= direction.y;
    }
    cout << "vx: " << force.x << " vy: " << force.y << endl;
    force *= thrustFactor;

    moveable->applyForce(force);
  }

  void Thrust::handleRotationKey(aronnax::EvUserRotation& ev,
      aronnax::Entity& entity)
  {
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto thrustable = entity.getComponent<Thrustable>(
        COMPONENT_TYPE_THRUSTABLE);
    auto thrustFactor = thrustable->getFactor();

    auto torque = ev.getDirection() * thrustFactor * 3;

    moveable->applyTorque(torque);
  }

  const string& Thrust::getType()
  {
    return COMPONENT_TYPE_THRUSTABLE;
  }

}

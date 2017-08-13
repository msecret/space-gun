
#ifndef _h_Moveable
#define _h_Moveable

#include <string>

#include <Box2D/Box2D.h>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

#include "alias.h"

namespace spacegun {
  using namespace std;
  using aronnax::Entity;

  const string COMPONENT_TYPE_MOVEABLE = "moveable";

  class Moveable : public aronnax::Component
  {
    public:
      Moveable();
      Moveable(const Vector2d& initialVel,
               const Vector2d& initialPos);
      Moveable(const Vector2d& initialVel,
               const Vector2d& initialPos,
               float initialAngle);
      void init(World& world, b2Shape& shape, Entity& e);
      const string getType();
      Vector2d getVel();
      // TODO should this be set force?
      void setVel(Vector2d newVel);
      Vector2d getPos();
      void setPos(Vector2d newPos);
      void setTransform(Vector2d newPos);
      Vector2d getInitialPosition();
      void move(Vector2d vel);
      float getAngle();
      float getFriction();
      void setFriction(float friction);
      float getRestitution();
      void setRestitution(float restitution);
      float getDensity();
      void setDensity(float density);
      float getMass();
      void setMass(float mass, const Vector2d& center,
          float inertia);

      void applyForce(const Vector2d& v);
      void applyTorque(float torque);

      Body* getBody();

    private:
      Vector2d initialPos_;
      Body* body_;
      BodyDef bodyDef_;
      Fixture* fixture_;
      FixtureDef fixtureDef_;
      MassData massData_;
      bool setMassData_;

  };
}

#endif

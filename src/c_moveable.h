
#ifndef _h_Moveable
#define _h_Moveable

#include <string>

#include <Box2D/Box2D.h>

#include "lib/component.h"
#include "lib/units.h"

#include "alias.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_MOVEABLE = "moveable";

  class Moveable : public aronnax::Component
  {
    public:
      Moveable();
      Moveable(const Vector2d& initialVel,
               const Vector2d& initialPos);
      void init(World& world, PolygonShape& shape);
      const string getType();
      Vector2d getVel();
      void setVel(Vector2d newVel);
      Vector2d getPos();
      void setPos(Vector2d newPos);
      void move(Vector2d vel);
      float getFriction();
      void setFriction(float friction);
      float getRestitution();
      void setRestitution(float restitution);
      float getDensity();
      void setDensity(float density);
      Body* getBody();

    private:
      Body* body_;
      BodyDef bodyDef_;
      Fixture* fixture_;
      FixtureDef fixtureDef_;

  };
}

#endif


#include "lib/units.h"

#include <Box2D/Box2D.h>

namespace spacegun {
  using namespace aronnax;

  using Body = b2Body;
  using BodyDef = b2BodyDef;
  using Fixture = b2Fixture;
  using FixtureDef = b2FixtureDef;
  using LineJoint = b2PrismaticJoint;
  using LineJointDef = b2PrismaticJointDef;
  using MassData = b2MassData;
  using Shape = b2Shape;
  using PolygonShape = b2PolygonShape;
  using World = b2World;

  using Vector2d = b2Vec2;
}

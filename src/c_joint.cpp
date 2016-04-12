
#include <Box2D/Box2D.h>

#include "lib/entity.h"

#include "c_moveable.h"
#include "c_joint.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;

  extern const string COMPONENT_TYPE_JOINT;

  void Joint::init(Body& bA, Body& bB, World& world)
  {
    lineJointDef_.bodyA = &bA;
    lineJointDef_.bodyB = &bB;

    world.CreateJoint(&lineJointDef_);
  }

  Entity* Joint::getOtherEntity()
  {
    return connectedBody_;
  }

  const string Joint::getType()
  {
    return COMPONENT_TYPE_JOINT;
  }
}

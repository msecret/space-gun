
#include <Box2D/Box2D.h>

#include "lib/entity.h"

#include "c_moveable.h"
#include "c_joint_solid.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;

  extern const string COMPONENT_TYPE_JOINT;

  void JointSolid::init(Body& bA, Body& bB, World& world)
  {
    if (!isJoint_) {
      jointDef_.bodyA = &bA;
      jointDef_.bodyB = &bB;

      world.CreateJoint(&jointDef_);
    }
  }

  Entity* JointSolid::getOtherEntity()
  {
    return connectedBody_;
  }

  const string JointSolid::getType()
  {
    return COMPONENT_TYPE_JOINT;
  }

  bool JointSolid::isJoint()
  {
    return isJoint_;
  }
}


#include <Box2D/Box2D.h>

#include "lib/entity.h"

#include "c_moveable.h"
#include "c_joint_solid.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;

  extern const string COMPONENT_TYPE_JOINT;

  void JointSolid::init(World& world)
  {
    auto moveableA = jointA_->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto moveableB = jointB_->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto bA = moveableA->getBody();
    auto bB = moveableB->getBody();

    // configurable
    jointDef_.localAnchorA = Vector2d(-20, -35);
    jointDef_.localAnchorB = Vector2d(20, 35);
    jointDef_.bodyA = bA;
    jointDef_.bodyB = bB;

    world.CreateJoint(&jointDef_);
  }

  Entity* JointSolid::getEntityA()
  {
    return jointA_;
  }

  Entity* JointSolid::getEntityB()
  {
    return jointB_;
  }
}

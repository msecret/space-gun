
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

    jointDef_.localAnchorA = -relativeAnchor_;
    jointDef_.localAnchorB = relativeAnchor_;
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

  void JointSolid::setRelativeAnchor(Vector2d anchor)
  {
    relativeAnchor_ = anchor;
  }
}

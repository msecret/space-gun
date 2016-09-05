
#include <Box2D/Box2D.h>

#include "lib/entity.h"

#include "c_moveable.h"
#include "c_joint_prismatic.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;

  extern const string COMPONENT_TYPE_JOINT;

  void JointPrismatic::init(World& world)
  {
    auto moveableA = jointA_->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto moveableB = jointB_->getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto bA = moveableA->getBody();
    auto bB = moveableB->getBody();

    auto bAPos = moveableA->getPos();
    moveableB->setDensity(2.0f);

    jointDef_.localAnchorA = relativeAnchor_;
    jointDef_.lowerTranslation = translation_.x;
    jointDef_.upperTranslation = translation_.y;
    jointDef_.localAnchorA = Vector2d(-20, -35);
    jointDef_.localAnchorB = Vector2d(20, 35);
    jointDef_.bodyA = bA;
    jointDef_.bodyB = bB;

    world.CreateJoint(&jointDef_);
  }

  // TODO move to base class
  Entity* JointPrismatic::getEntityA()
  {
    return jointA_;
  }

  Entity* JointPrismatic::getEntityB()
  {
    return jointB_;
  }

  void JointPrismatic::setRelativeAnchor(Vector2d anchor)
  {
    relativeAnchor_ = anchor;
  }

  void JointPrismatic::setTranslation(float lowerTranslation,
      float upperTranslation)
  {
    translation_.x = lowerTranslation;
    translation_.y = upperTranslation;
  }
}

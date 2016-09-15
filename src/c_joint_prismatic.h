
#ifndef _h_JointPrismatic
#define _h_JointPrismatic

#include <string>

#include <Box2D/Box2D.h>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

#include "alias.h"
#include "c_joint.h"

namespace spacegun {
  using std::string;
  using aronnax::Component;
  using aronnax::Entity;
  using aronnax::Vector2d;

  struct JointMotor
  {
    float maxMotorForce, motorSpeed;

    JointMotor(float maxSpeed, float speed) :
      maxMotorForce(maxSpeed),
      motorSpeed(speed)
    { }
  };

  class JointPrismatic : public Joint
  {
    public:
      JointPrismatic(Entity* entityA, Entity* entityB, JointMotor* motor) :
        jointA_(entityA),
        jointB_(entityB)
      {
        jointDef_.collideConnected = false;
        jointDef_.enableLimit = true;

        if (motor) {
          jointDef_.enableMotor = true;
          jointDef_.maxMotorForce = motor->maxMotorForce;
          jointDef_.motorSpeed = -motor->motorSpeed;
        }
      }
      void init(World& world);
      Entity* getEntityA();
      Entity* getEntityB();
      void setRelativeAnchor(Vector2d anchor);
      void setTranslation(float lowerTranslation, float upperTranslation);

    private:
      Entity* jointA_;
      Entity* jointB_;
      b2PrismaticJoint* joint_;
      b2PrismaticJointDef jointDef_;
      Vector2d relativeAnchor_;
      Vector2d translation_;
  };
}

#endif

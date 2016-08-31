
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

  class JointPrismatic : public Joint
  {
    public:
      JointPrismatic(Entity* entityA, Entity* entityB) :
        jointA_(entityA),
        jointB_(entityB)
      {
        // TODO make configurable
        jointDef_.collideConnected = false;
        jointDef_.enableLimit = true;
        // configurable
        jointDef_.enableMotor = true;
        // configurable
        jointDef_.localAnchorA = Vector2d(-40.0f, 0);
        // configurable
        jointDef_.lowerTranslation = -25.0f;
        // configurable
        jointDef_.upperTranslation = 30.0f;
        // configurable
        jointDef_.maxMotorForce = 1.5;
        // configurable
        jointDef_.motorSpeed = -0.5;
      }
      void init(World& world);
      Entity* getEntityA();
      Entity* getEntityB();
      const string getType();

    private:
      Entity* jointA_;
      Entity* jointB_;
      b2PrismaticJoint* joint_;
      b2PrismaticJointDef jointDef_;
  };
}

#endif

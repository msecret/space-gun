
#ifndef _h_Joint
#define _h_Joint

#include <string>

#include <Box2D/Box2D.h>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

#include "alias.h"

namespace spacegun {
  using std::string;
  using aronnax::Component;
  using aronnax::Entity;
  using aronnax::Vector2d;

  const string COMPONENT_TYPE_JOINT = "joint";

  class Joint: public Component
  {
    public:
      Joint(Entity* entity) :
        connectedBody_(entity),
        isJoint_(false)
      {
        lineJointDef_.collideConnected = true;
        lineJointDef_.localAnchorA = Vector2d(27.0f, 0);
        lineJointDef_.length = 27.0f;
        lineJointDef_.frequencyHz = 0.1f;
        lineJointDef_.dampingRatio = 0.9f;
        prismaticJointDef_.collideConnected = false;
        prismaticJointDef_.enableLimit = true;
        prismaticJointDef_.enableMotor = true;
        prismaticJointDef_.localAnchorA = Vector2d(-40.0f, 0);
        prismaticJointDef_.lowerTranslation = -25.0f;
        prismaticJointDef_.upperTranslation = 30.0f;
        prismaticJointDef_.maxMotorForce = 1.5;
        prismaticJointDef_.motorSpeed = -0.5;
      }
      Joint(Entity* entity, bool isJoint) :
        connectedBody_(entity),
        isJoint_(isJoint)
      { }
      void init(Body& bA, Body& bB, World& world);
      Entity* getOtherEntity();
      const string getType();

    private:
      Entity* connectedBody_;
      b2DistanceJoint* lineJoint_;
      b2DistanceJointDef lineJointDef_;
      b2PrismaticJoint* prismaticJoint_;
      b2PrismaticJointDef prismaticJointDef_;
      bool isJoint_;
  };
}

#endif

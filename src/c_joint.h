
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
        connectedBody_(entity)
      {
        lineJointDef_.collideConnected = false;
        lineJointDef_.localAnchorA = Vector2d(-80.0f, 0);
        lineJointDef_.length = -60.0f;
        lineJointDef_.frequencyHz = 0.1f;
        lineJointDef_.dampingRatio = 0.9f;
        prismaticJointDef_.collideConnected = false;
        prismaticJointDef_.enableLimit = true;
        prismaticJointDef_.enableMotor = false;
        prismaticJointDef_.localAnchorA = Vector2d(-50.0f, 0);
        prismaticJointDef_.lowerTranslation = 0.0f;
        prismaticJointDef_.upperTranslation = 0.0f;
      }
      void init(Body& bA, Body& bB, World& world);
      Entity* getOtherEntity();
      const string getType();

    private:
      Entity* connectedBody_;
      b2DistanceJoint* lineJoint_;
      b2DistanceJointDef lineJointDef_;
      b2PrismaticJoint* prismaticJoint_;
      b2PrismaticJointDef prismaticJointDef_;
  };
}

#endif

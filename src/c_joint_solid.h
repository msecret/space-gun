
#ifndef _h_JointSolid
#define _h_JointSolid

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

  class JointSolid: public Component
  {
    public:
      JointSolid(Entity* entity) :
        connectedBody_(entity),
        isJoint_(false)
      {
        jointDef_.referenceAngle = 1.5708;
        jointDef_.dampingRatio= 1;
      }
      JointSolid(Entity* entity, bool isJoint) :
        connectedBody_(entity),
        isJoint_(isJoint)
      { }
      void init(Body& bA, Body& bB, World& world);
      Entity* getOtherEntity();
      const string getType();
      bool isJoint();

    private:
      Entity* connectedBody_;
      b2WeldJoint* joint_;
      b2WeldJointDef jointDef_;
      bool isJoint_;
  };
}

#endif

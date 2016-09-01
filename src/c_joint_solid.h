
#ifndef _h_JointSolid
#define _h_JointSolid

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

  class JointSolid : public Joint
  {
    public:
      JointSolid(Entity* entityA, Entity* entityB) :
        jointA_(entityA),
        jointB_(entityB)
      {
        jointDef_.dampingRatio = 0.5;
        // Configurable
        jointDef_.referenceAngle = 1.508;
      }
      void init(World& world);
      Entity* getEntityA();
      Entity* getEntityB();

    private:
      Entity* jointA_;
      Entity* jointB_;
      b2WeldJoint* joint_;
      b2WeldJointDef jointDef_;
  };
}

#endif

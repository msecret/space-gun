
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
      virtual ~Joint() {};
      virtual void init(World& world) {};
      virtual Entity* getEntityA() {};
      virtual Entity* getEntityB() {};
      virtual const string getType();
  };
}

#endif


#ifndef _h_Universal
#define _h_Universal

#include <string>

#include "alias.h"

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using std::string;

  const string COMPONENT_TYPE_UNIVERSAL = "universal";

  class Universal : public aronnax::Component
  {
    public:
      Universal(World& world)
        : world_(&world)
      { }
      Universal(World& world, float timeStep):
        world_(&world),
        timeStep_(timeStep)
      { }
      const string getType();
      World* getWorld();
      float getTimeStep();

    private:
      World* world_;
      float timeStep_;
  };

}

#endif

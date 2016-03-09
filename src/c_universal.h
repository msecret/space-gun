
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
      const string getType();
      World* getWorld();

    private:
      World* world_;
  };

}

#endif

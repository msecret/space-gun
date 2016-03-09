
#include <string>

#include "lib/entity.h"
#include "lib/units.h"

#include "alias.h"
#include "c_universal.h"

namespace spacegun {
  using std::string;

  extern const string COMPONENT_TYPE_UNIVERSAL;

  const string Universal::getType()
  {
    return COMPONENT_TYPE_UNIVERSAL;
  }

  World* Universal::getWorld()
  {
    return world_;
  }

}

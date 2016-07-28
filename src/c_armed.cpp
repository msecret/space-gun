
#include <Box2D/Box2D.h>

#include "lib/entity.h"

#include "c_armed.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;

  extern const string COMPONENT_TYPE_ARMED;

  Entity* Armed::getWeapon()
  {
    return weaponEntity_;
  }

  const string Armed::getType()
  {
    return COMPONENT_TYPE_ARMED;
  }
}

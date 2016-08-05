
#include <cstdio>
#include <iostream>

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

  void Armed::activate() {
    using std::cout;
    using std::endl;
    cout << "in armed -> activate" << endl;
  }
}

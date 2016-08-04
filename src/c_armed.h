

#ifndef _h_Armed
#define _h_Armed

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

  const string COMPONENT_TYPE_ARMED = "armed";

  class Armed: public Component
  {
    public:
      Armed(Entity* entity) :
        weaponEntity_(entity)
      { }
      const string getType();
      Entity* getWeapon();
      void activate();

    private:
      Entity* weaponEntity_;
  };
}

#endif

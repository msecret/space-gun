
#include <algorithm>
#include <cmath>

#include "lib/units.h"
#include "c_armed.h"
#include "s_arm.h"

namespace spacegun {
  using std::string;

  using aronnax::EV_WEAPON_FIRED;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvWeaponFired;

  extern const string COMPONENT_TYPE_ARMED;

  void Arm::init(Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
    }
  }

  void Arm::onAddEntity(Entity& entity)
  {
    bindEntity(entity);
  }

  void Arm::bindEntity(Entity& entity)
  {
    entity.on(EV_WEAPON_FIRED,
        [&](EvWeaponFired* ev) {
      activateWeapon(*ev, entity);
    });
  }

  void Arm::activateWeapon(EvWeaponFired& ev, Entity& entity)
  {
    if (entity.hasComponent(COMPONENT_TYPE_ARMED)) {
      auto armed = entity.getComponent<Armed>(COMPONENT_TYPE_ARMED);
      armed->activate();
    }
  }

  const string& Arm::getType()
  {
    return COMPONENT_TYPE_ARMED;
  }

}

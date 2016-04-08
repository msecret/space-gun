
#include "lib/units.h"
#include "s_damage.h"

#include "c_damageable.h"

namespace spacegun {
  using std::string;

  using aronnax::EV_PLAYER_DEATH;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvPlayerDeath;

  extern const string COMPONENT_TYPE_DAMAGEABLE;

  void Damage::update(const uint32_t dt, Entities& entities)
  {
    for (auto e : entities) {
      emitIfDead(*e);
    }
  }

  bool Damage::checkHealth(Entity& entity)
  {
    auto c = entity.getComponent<Damageable>(COMPONENT_TYPE_DAMAGEABLE);
    auto health = c->getHealth();
    if (health <= 0) {
      return true;
    }
    return false;
  }

  void Damage::emitIfDead(Entity& entity)
  {
    if (checkHealth(entity)) {
      EvPlayerDeath ev;
      entity.emit(EV_PLAYER_DEATH, &ev);
    }
  }

  const string& Damage::getType()
  {
    return COMPONENT_TYPE_DAMAGEABLE;
  }

}

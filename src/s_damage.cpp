
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stdio.h>

#include "lib/entity.h"
#include "lib/renderer.h"
#include "lib/units.h"

#include "c_damageable.h"
#include "s_damage.h"

namespace spacegun {
  using std::endl;
  using std::ostringstream;
  using std::string;
  using aronnax::Color;
  using aronnax::EV_PLAYER_DEATH;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvPlayerDeath;
  using aronnax::IRenderer;
  using aronnax::Vector2d;

  extern const string COMPONENT_TYPE_DAMAGEABLE;

  void Damage::update(const uint32_t dt, Entities& entities)
  {
    for (auto e : entities) {
      this->writeHealth(*e);
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

  void Damage::writeHealth(Entity& e)
  {
    if (renderer_) {
      auto c = e.getComponent<Damageable>(COMPONENT_TYPE_DAMAGEABLE);

      Vector2d pos = { 200, 200 };
      ostringstream buffer;
      buffer << "health: " << c->getHealth();;
      string msg(buffer.str());

      Color color(250, 250, 250, 255);
      renderer_->drawText(pos, msg, color);
    }
  }

  const string& Damage::getType()
  {
    return COMPONENT_TYPE_DAMAGEABLE;
  }

}

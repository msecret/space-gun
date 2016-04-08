
#include <iostream>

#include "lib/units.h"
#include "s_death.h"

#include "c_damageable.h"
#include "c_mortal.h"
#include "c_moveable.h"

namespace spacegun {
  using std::string;

  using aronnax::EV_PLAYER_DEATH;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvPlayerDeath;
  using aronnax::Vector2d;

  extern const string COMPONENT_TYPE_MORTAL;

  void Death::init(Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
    }
  }

  void Death::onAddEntity(Entity& entity)
  {
    bindEntity(entity);
  }

  void Death::bindEntity(Entity& entity)
  {
    entity.on(EV_PLAYER_DEATH,
        [&](EvPlayerDeath* ev) {
      resetEntity(entity);
    });
  }

  void Death::resetEntity(Entity& entity)
  {
    auto damageable = entity.getComponent<Damageable>(
        COMPONENT_TYPE_DAMAGEABLE);
    auto mortal = entity.getComponent<Mortal>(COMPONENT_TYPE_MORTAL);
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);

    Vector2d pos = { 60, 60 };
    Vector2d vel = { 0 , 0 };

    damageable->resetHealth();
    moveable->setPos(pos);
    moveable->setVel(vel);
    mortal->addDeath();

    using std::cout;
    using std::endl;
    cout << "Player death " << mortal->getDeaths() << endl;
  }

  const string& Death::getType()
  {
    return COMPONENT_TYPE_MORTAL;
  }

}

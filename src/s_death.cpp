
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "lib/units.h"
#include "s_death.h"

#include "c_damageable.h"
#include "c_mortal.h"
#include "c_moveable.h"
#include "c_notification.h"

namespace spacegun {
  using std::string;

  using aronnax::EV_PLAYER_DEATH;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvImpact;
  using aronnax::EvPlayerDeath;
  using aronnax::Vector2d;

  extern const string COMPONENT_TYPE_MORTAL;
  extern const string COMPONENT_TYPE_NOTIFICATION;

  void Death::init(Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
      if (e->hasComponent(COMPONENT_TYPE_NOTIFICATION)) {
        auto m = e->getComponent<Mortal>(COMPONENT_TYPE_MORTAL);
        auto n = e->getComponent<Notification>(
            COMPONENT_TYPE_NOTIFICATION);
        int lineNum = n->addLine(" ");
        m->notificationLine = lineNum;
      }
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

    Vector2d pos = moveable->getInitialPosition();
    Vector2d vel = { 0 , 0 };

    damageable->resetHealth();
    moveable->setPos(pos);
    moveable->setVel(vel);
    mortal->addDeath();

    std::ostringstream buffer;
    buffer << "deaths: " << mortal->getDeaths();
    std::string msg = buffer.str();
    using std::cout;
    using std::endl;
    cout << msg << endl;
    if (entity.hasComponent(COMPONENT_TYPE_NOTIFICATION)) {
      auto s = entity.getComponent<Notification>(COMPONENT_TYPE_NOTIFICATION);
      auto lineNum = mortal->notificationLine;
      s->updateLine(lineNum, msg);
      vector<float> total;
      total.push_back(0.0);
      EvImpact ev(total);
      entity.emit(EV_IMPACT, &ev);
    }
  }

  const string& Death::getType()
  {
    return COMPONENT_TYPE_MORTAL;
  }

}

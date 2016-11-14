
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

#include "lib/units.h"
#include "s_impacts.h"

#include "c_damageable.h"
#include "c_notification.h"

namespace spacegun {
  using std::endl;
  using std::string;
  using std::ostringstream;

  using aronnax::EV_IMPACT;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvImpact;

  extern const string COMPONENT_TYPE_DAMAGEABLE;

  void Impacts::init(Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);

      if (e->hasComponent(COMPONENT_TYPE_NOTIFICATION)) {
        auto c = e->getComponent<Damageable>(COMPONENT_TYPE_DAMAGEABLE);
        auto n = e->getComponent<Notification>(
            COMPONENT_TYPE_NOTIFICATION);
        std::ostringstream buffer;
        buffer << "health: " << int(c->getHealth());
        std::string msg = buffer.str();
        int lineNum = n->addLine(msg);
        c->notificationLine = lineNum;
      }
    }
  }

  void Impacts::onAddEntity(Entity& entity)
  {
    bindEntity(entity);
  }

  void Impacts::bindEntity(Entity& entity)
  {
    entity.on(EV_IMPACT,
        [&](EvImpact* ev) {
      handleImpact(entity, *ev);
    });
    entity.on(EV_PLAYER_DEATH,
        [&](EvPlayerDeath* ev) {
      handleDeath(entity);
    });
  }

  void Impacts::handleImpact(Entity& entity, EvImpact& ev)
  {
    auto c = entity.getComponent<Damageable>(COMPONENT_TYPE_DAMAGEABLE);
    auto firstImpulse = ev.getImpulses()[0];

    c->applyDamage(firstImpulse);

    if (entity.hasComponent(COMPONENT_TYPE_NOTIFICATION)) {
      std::ostringstream buffer;
      buffer << "health: " << int(c->getHealth());
      std::string msg = buffer.str();
      using std::cout;
      using std::endl;
      cout << msg << endl;
      auto s = entity.getComponent<Notification>(COMPONENT_TYPE_NOTIFICATION);
      auto lineNum = c->notificationLine;
      s->updateLine(lineNum, msg);
    }
  }

  void Impacts::handleDeath(Entity& entity)
  {
    auto c = entity.getComponent<Damageable>(COMPONENT_TYPE_DAMAGEABLE);

    if (entity.hasComponent(COMPONENT_TYPE_NOTIFICATION)) {
      using std::cout;
      using std::endl;
      cout << "reset notification" << endl;
      std::ostringstream buffer;
      buffer << "health: " << int(c->getHealth());
      std::string msg = buffer.str();
      auto s = entity.getComponent<Notification>(COMPONENT_TYPE_NOTIFICATION);
      auto lineNum = c->notificationLine;
      s->updateLine(lineNum, msg);
    }
  }

  const string& Impacts::getType()
  {
    // TODO should this impact component be linked to damageable component.
    return COMPONENT_TYPE_DAMAGEABLE;
  }

}


#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>

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
        string* line = n->addLine(msg);
        c->healthNotification = line;
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
      *c->healthNotification = msg;
    }
  }

  const string& Impacts::getType()
  {
    // TODO should this impact component be linked to damageable component.
    return COMPONENT_TYPE_DAMAGEABLE;
  }

}

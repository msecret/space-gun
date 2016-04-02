
#include "lib/units.h"
#include "s_impacts.h"

#include "c_damageable.h"

namespace spacegun {
  using std::string;

  using aronnax::EV_IMPACT;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvImpact;

  extern const string COMPONENT_TYPE_DAMAGEABLE;

  void Impacts::init(Entities& entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
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
  }

  const string& Impacts::getType()
  {
    // TODO should this impact component be linked to damageable component.
    return COMPONENT_TYPE_DAMAGEABLE;
  }

}

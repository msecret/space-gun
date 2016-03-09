
#include <string>

#include "lib/entity.h"

#include "s_movement.h"
#include "c_moveable.h"
#include "c_universal.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;
  using aronnax::Entities;

  extern const string COMPONENT_TYPE_MOVEABLE;

  void Movement::init(Entities entities)
  {
    for (auto e : entities) {
      bindEntity(*e);
    }
  }

  void Movement::onAddEntity(Entity& entity)
  {
    bindEntity(entity);
  }

  const string& Movement::getType()
  {
    return COMPONENT_TYPE_MOVEABLE;
  }

  void Movement::bindEntity(Entity& e)
  {
    auto c = e.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto u = e.getComponent<Universal>(COMPONENT_TYPE_UNIVERSAL);
    auto world = u->getWorld();
    c->init(*world);
  }

}

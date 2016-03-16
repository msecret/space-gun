
#include <string>

#include "lib/entity.h"

#include "s_movement.h"
#include "c_moveable.h"
#include "c_rectangular.h"
#include "c_universal.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;
  using aronnax::Entities;

  extern const string COMPONENT_TYPE_MOVEABLE;

  void Movement::init(Entities& entities)
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
    if (e.hasComponent(COMPONENT_TYPE_RECTANGULAR)) {
      auto s = e.getComponent<Rectangular>(COMPONENT_TYPE_RECTANGULAR);
      auto m = e.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
      auto u = e.getComponent<Universal>(COMPONENT_TYPE_UNIVERSAL);
      auto world = u->getWorld();

      auto shape = s->getShape();

      m->init(*world, *shape);
    }
    else {
      throw std::logic_error("Movement system requires shape component");
    }
  }

}

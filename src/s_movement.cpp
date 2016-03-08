
#include "lib/entity.h"

#include "s_movement.h"
#include "c_moveable.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_MOVEABLE;

  const string& Movement::getType()
  {
    return COMPONENT_TYPE_MOVEABLE;
  }

  void Movement::update(const uint32_t dt, aronnax::Entities& entities)
  {
    for (auto e : entities) {
      this->processMovement(dt, *e);
    }
  }

  void Movement::processMovement(const uint32_t dt, aronnax::Entity& entity)
  {
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    Vector2d vel = moveable->getVel();
    moveable->move(vel);
  }
}

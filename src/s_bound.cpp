
#include <cstdio>

#include "lib/entity.h"

#include "c_boundable.h"
#include "c_joint.h"
#include "c_moveable.h"
#include "s_bound.h"

namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_BOUNDABLE;

  const string& Bound::getType()
  {
    return COMPONENT_TYPE_BOUNDABLE;
  }

  void Bound::update(const uint32_t dt, aronnax::Entities& entities)
  {
    for (auto e : entities) {
      this->checkBounds(dt, *e);
    }
  }

  void Bound::checkBounds(const uint32_t dt, aronnax::Entity& entity)
  {
    Vector2d newPos;
    auto bounds = entity.getComponent<Boundable>(COMPONENT_TYPE_BOUNDABLE)
        ->getBounds();
    auto moveable = entity.getComponent<Moveable>(COMPONENT_TYPE_MOVEABLE);
    auto currentPos = moveable->getPos();

    newPos.x = wrapAround(currentPos.x, bounds.x);
    newPos.y = wrapAround(currentPos.y, bounds.y);

    moveable->setPos(newPos);
    if (entity.hasComponent(COMPONENT_TYPE_JOINT)) {
      auto joint = entity.getComponent<Joint>(COMPONENT_TYPE_JOINT);
    }
  }

  float Bound::wrapAround(float coordinate, float max)
  {
    if (coordinate < 0) {
      return max;
    }
    if (coordinate > max) {
      return 0;
    }

    return coordinate;
  }
}

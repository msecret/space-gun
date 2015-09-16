
#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"
#include "moveable.h"

namespace spacegun {

void Moveable::update(aronnax::Entity &entity, const uint32_t dt)
{
  entity.pos.x += entity.v.x;
  entity.pos.y += entity.v.y;
}

}

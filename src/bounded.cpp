
#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"
#include "bounded.h"
#include "world.h"

namespace spacegun {

void Bounded::update(aronnax::Entity &entity, const uint32_t dt)
{
  entity.pos.x = wrapAround(entity.pos.x, WORLD_W); 
  entity.pos.y = wrapAround(entity.pos.y, WORLD_H); 
}

double Bounded::wrapAround(double coordinate, double max) {
  if (coordinate < 0) {
    return max;
  }
  if (coordinate > max) {
    return 0;
  }

  return coordinate;
}

std::string Bounded::getType()
{
  return "Bounded";
}

}


#include <cstdint>
#include <iostream>
#include <string>
#include <stdio.h>

#include "SDL2/SDL.h"

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

std::string Moveable::getType()
{
  return "Moveable";
}

}


#include <cstdint>
#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"
#include "moveable.h"

namespace spacegun {

void Moveable::update(aronnax::Entity &entity, const uint32_t dt)
{
  SDL_Log("circle render");
  printf("moveable update");
  entity.pos.x += entity.v.x;
  entity.pos.y += entity.v.y;
}

}

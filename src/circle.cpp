
#include <cstdint>
#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"
#include "circle.h"

namespace spacegun {

void Circular::render(aronnax::Entity &entity)
{
  SDL_Log("circle render");
  entity.getRenderer()->drawCircle(
    entity.pos,
    entity.box
    );
}

}


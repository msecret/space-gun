
#include <cstdint>
#include <iostream>
#include <string>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"
#include "circle.h"

namespace spacegun {

void Circular::render(aronnax::Entity &entity)
{
  entity.getRenderer()->drawCircle(
    entity.pos,
    entity.box
    );
}

std::string Circular::getType()
{
  return "Circular";
}

}


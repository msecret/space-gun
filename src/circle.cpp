
#include <cstdint>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"
#include "circle.h"

namespace spacegun {

void Circular::render(aronnax::Entity &entity)
{
  entity.get()->renderer->drawCircle(
    entity.get()->pos,
    entity.get()->box
    );
}

}


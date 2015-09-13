
#include "lib/component.h"
#include "lib/entity.h"
#include "lib/positioning.h"
#include "moveable.h"

void Moveable::update(Entity* entity, const int dt)
{
  entity->pos.x += entity->v.x;
  entity->pos.y += entity->v.y;
}


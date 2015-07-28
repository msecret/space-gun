
#include "../lib/component.h"
#include "../lib/entity.h"
#include "../lib/positioning.h"
#include "moveable.h"

void Moveable::init(Entity* entity, Vector2d v)
{
  entity->v = v;
}

void Moveable::update(Entity* entity, int dt)
{
  entity->v = Vector2d { x: 1.0, y: 1.0 };
}

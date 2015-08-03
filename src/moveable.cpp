
#include "lib/component.h"
#include "lib/entity.h"
#include "lib/positioning.h"
#include "moveable.h"

Moveable::Moveable(Entity* entity, const Vector2d & v)
{
  entity_ = entity;
}

void Moveable::update(Entity* entity, int dt)
{
  entity->pos.x += entity->v.x;
  entity->pos.y += entity->v.y;
}

void Moveable::receive(int message)
{
}

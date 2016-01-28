
#include <cstdint>
#include <string>

#include "SDL2/SDL.h"

#include "lib/compentityAnt.h"
#include "lib/entity.h"
#include "lib/events.h"
#include "lib/units.h"
#include "collision.h"

namespace spacegun {

void Collidable::init(aronnax::Entity &entity)
{
  entity.on(COLLISION, [&](aronnax::Collsion) {

  }); 
}

void Collidable:update(aronnax::Entity &entityA, const uint32_t dt)
{

}

void Collidable::update(aronnax::Entity &entityA, aronnax::Entity &entityB, 
        const uint32_t dt)
{
  aronnax::Collision collision;
  bool collisionX = entityA.pos.x + entityA.box.x >= entityB.pos.x &&
      entityB.pos.x + entityB.box.x >= entityA.pos.x;

  bool collisionY = entityA.pos.y + entityA.box.y >= entityB.pos.y &&
      entityB.pos.y + entityB.box.y >= entityA.pos.y;

  if (collisionX && collisionY) {
    Vector2d pos = { entityA.pos.x, entityA.box.x };
    collision = {
      entityA,
      entityB,
      pos 
    };
    entity.emit(COLLISION, collision);
  }
}

std::string Collidable::getType()
{
  return "Collidable";
}

}

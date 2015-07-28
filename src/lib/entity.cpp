
#include "component.h"
#include "entity.h"
#include "renderer.h"

Entity::Entity(std::vector<Component> components):
  components_(components)
  { }

void Entity::update(int dt)
{
  for(std::vector<Component>::iterator it = components_.begin();
      it != components_.end(); ++it) {
    (*it).update(dt);
  }
}

void Entity::render()
{
}

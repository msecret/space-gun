
#include <memory>

#include "component.h"
#include "entity.h"
#include "renderer.h"

Entity::Entity(std::vector<std::shared_ptr<Component>> components):
  components_(components)
  { }

void Entity::update(const int dt)
{
  for (unsigned int i = 0; i < components_.size(); ++i) {
    components_[i]->update(this, dt);
  }
}

void Entity::render()
{
}

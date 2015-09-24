
#include <memory>

#include "component.h"
#include "entity.h"
#include "renderer.h"

namespace aronnax {

Entity::Entity(Components components):
  components_(components)
  { }

Entity::Entity(Components components,
               std::shared_ptr<Renderer> renderer):
  components_(components),
  renderer_(renderer)
  { }

void Entity::update(const uint32_t dt)
{
  for (unsigned int i = 0; i < components_.size(); ++i) {
    components_[i].update(*this, dt);
  }
}

void Entity::render()
{
  for (unsigned int i = 0; i < components_.size(); ++i) {
    components_[i].render(*this);
  }
}

Renderer* Entity::getRenderer()
{
  return renderer_.get();
}

}

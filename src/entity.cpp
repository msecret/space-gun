
#include "component/component.h"
#include "entity.h"
#include "renderer.h"

Entity::Entity(Renderer* renderer,
               std::vector<Component*> components):
  renderer_(renderer),
  components_(components)
  { }

void Entity::update(int dt)
{
  for(std::vector<Component*>::iterator it = components_.begin();
      it != components_.end(); ++it) {
    (*it)->update(dt);
  }
}

void Entity::render()
{
  renderer_->render();
}

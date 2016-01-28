
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>

#include "SDL2/SDL.h"

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
{ 
}

void Entity::update(const uint32_t dt)
{
  for (unsigned int i = 0; i < components_.size(); ++i) {
    components_[i]->update(*this, dt);
  }
}

void Entity::render()
{
  for (unsigned int i = 0; i < components_.size(); ++i) {
    //std::cout << "component type: " << components_[i].getType() << "\n";
    components_[i]->render(*this);
  }
}

Renderer* Entity::getRenderer()
{
  return renderer_.get();
}

// TODO improve performance by setting on constructor and addComponent.
bool Entity::hasComponent(std::string componentType)
{
  for (unsigned int i = 0; i < components_.size(); ++i) {
    if (components_[i]->getType() == componentType) {
      return true;
    }
  }
  return false;
}

Component* Entity::getComponent(std::string componentType)
{
  for (unsigned int i = 0; i < components_.size(); ++i) {
    if (components_[i]->getType() == componentType) {
      return components_[i];
    }
  }
  throw std::runtime_error("Attempt to access non-existant component");
}

}

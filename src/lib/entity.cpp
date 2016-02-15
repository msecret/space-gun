
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string>

#include "SDL2/SDL.h"

#include "component.h"
#include "entity.h"
#include "renderer.h"

namespace aronnax {
  using namespace std;

  Entity::Entity():
    components_()
  { }

  Entity::Entity(Components components):
    components_(components)
  { }


  // TODO improve performance by setting on constructor and addComponent.
  bool Entity::hasComponent(const string& componentType)
  {
    for (unsigned int i = 0; i < components_.size(); ++i) {
      if (components_[i]->getType() == componentType) {
        return true;
      }
    }
    return false;
  }

  void Entity::addComponent(Component* component) {
    if (!hasComponent(component->getType())) {
      components_.push_back(component);
    }
  }

  Components& Entity::getComponents()
  {
    return components_;
  }

  vector<string> Entity::getComponentTypes()
  {
    vector<string> componentTypes;

    for (auto c : components_) {
      componentTypes.push_back(c->getType());
    }

    return componentTypes;
  }

  const Vector2d& Entity::getPos()
  {
    return pos;
  }

  void Entity::setPos(const Vector2d& p)
  {
    pos = p;
  }

  void Entity::movePos(const Vector2d& vel)
  {
    pos += vel;
  }

}

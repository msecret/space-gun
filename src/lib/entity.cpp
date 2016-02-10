
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
    exit(1);
  }

  Components Entity::getComponents()
  {
    return components_;
  }

  std::vector<std::string> Entity::getComponentTypes()
  {
    std::vector<std::string> componentTypes;

    for (auto c : components_) {
      componentTypes.push_back(c->getType());
    }

    return componentTypes;
  }

}

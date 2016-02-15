
#ifndef _h_Entity
#define _h_Entity

#include <iostream>
#include <memory>
#include <set>
#include <stdio.h>
#include <string>
#include <vector>

#include "component.h"
#include "event_emitter.h"
#include "units.h"

namespace aronnax {
  using namespace std;

  class Entity : public EventEmitter
  {
    public:
      Entity();

      Entity(Components components);

      virtual ~Entity() {};

      virtual bool hasComponent(const string& componentType);

      void addComponent(Component* component);

      template <class TComponent>
      TComponent* getComponent(string componentType);

      Components getComponents();

      virtual vector<string> getComponentTypes();

      Vector2d getPos();

      void movePos(const Vector2d& vel);

    private:
      Vector2d pos;
      Components components_;

  };

  using Entities = vector<Entity*>;

  template <class TComponent>
  TComponent* Entity::getComponent(std::string componentType)
  {
    for (unsigned int i = 0; i < components_.size(); ++i) {
      if (components_[i]->getType() == componentType) {
        return static_cast<TComponent*>(components_[i]);
      }
    }
    exit(1);
  }

}

#endif

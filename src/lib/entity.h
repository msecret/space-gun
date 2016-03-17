
#ifndef _h_Entity
#define _h_Entity

#include <memory>
#include <set>
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
      TComponent* getComponent(const string& componentType);

      Components& getComponents();

      virtual vector<string> getComponentTypes();

    private:
      Components components_;

  };

  using Entities = vector<Entity*>;

  template <class TComponent>
  TComponent* Entity::getComponent(const string& componentType)
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

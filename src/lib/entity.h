
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

  class IEntity : public EventEmitter
  {
    public:
      virtual ~IEntity() {};

      virtual bool hasComponent(string componentType) = 0;
      
      virtual void addComponent(Component* component) =0;

      virtual Component* getComponent(string componentType) = 0;
      
      virtual vector<Component*> getComponents() = 0;

      virtual vector<string> getComponentTypes() =0;
  };

  using IEntities = vector<IEntity*>;
  using IEntitySet = set<IEntity*>;

  class Entity : public IEntity
  {
    public:
      Entity() {};

      Entity(Components components);

      bool hasComponent(string componentType);

      void addComponent(Component* component);

      Component* getComponent(string componentType);

      Components getComponents();

      vector<string> getComponentTypes();

    private:
      Vector2d pos;
      Components components_;

  };

}

#endif

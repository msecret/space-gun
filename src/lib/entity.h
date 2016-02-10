
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

  class IEntity : public EventEmitter
  {
    public:
      virtual ~IEntity() {};
      virtual bool hasComponent(std::string componentType) = 0;
      virtual Component* getComponent(std::string componentType) = 0;
      virtual Components getComponents() = 0;
      virtual std::vector<std::string> getComponentTypes() =0;
  };

  using IEntities = std::vector<IEntity*>;
  using IEntitySet = std::set<IEntity*>;

  class Entity : public IEntity
  {
    public:
      Entity() {};
      Entity(Components components);
      bool hasComponent(std::string componentType);
      Component* getComponent(std::string componentType);
      Components getComponents();
      std::vector<std::string> getComponentTypes();

    private:
      Vector2d pos;
      Components components_;

  };

}

#endif

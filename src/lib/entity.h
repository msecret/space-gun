
#ifndef _h_Entity
#define _h_Entity

#include <memory>
#include <set>
#include <string>

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
  };

  using IEntitySet = std::set<IEntity*>;

  class Entity : public IEntity
  {
    public:
      Entity(Components components);
      bool hasComponent(std::string componentType);
      Component* getComponent(std::string componentType);
      Components getComponents();

    private:
      Vector2d pos;
      Components components_;

  };

}

#endif

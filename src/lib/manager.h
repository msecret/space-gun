
#ifndef _h_Manager
#define _h_Manager

#include <initializer_list>
#include <memory>
#include <string>

#include "component.h"
#include "entity.h"
#include "system.h"

namespace aronnax {

  class Manager
  {
    public:
      Manager();
      void update(const uint32_t dt);
      void render(const uint32_t dt);
      IEntity& createEntity(Components components);
      void addEntity(IEntity& entity);
      //void removeEntity(const IEntity& entity);
      //void addSystem(const System& system);
      //System& getSystem(const std::string& systemType); 
      //void removeSystem(const System& system);
      IEntitySet& getEntities();

    private:
      IEntitySet entities_;
      Systems systems_;

  };

}

#endif


#ifndef _h_Manager
#define _h_Manager

#include <initializer_list>
#include <memory>
#include <string>

#include "component.h"
#include "entity.h"
#include "renderer.h"
#include "system.h"

namespace aronnax {
  using namespace std;

  class Manager
  {
    public:
      Manager();
      Manager(IRenderer& renderer);
      void update(const uint32_t dt);
      void render(const uint32_t dt);
      Entity& createEntity(Components components);
      void addEntity(Entity& entity);
      //void removeEntity(const Entity& entity);
      void addSystem(System* system);
      Systems& getSystems();
      Systems getSystems(const string& systemType); 
      //void removeSystem(const System& system);
      Entities& getEntities();
      Entities getEntities(const string& componentType);

    private:
      Entities entities_;
      Systems systems_;
      IRenderer* renderer_;

  };

}

#endif

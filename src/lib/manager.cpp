
#include <initializer_list>
#include <iostream>
#include <set>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "entity.h"
#include "manager.h"

namespace aronnax {

  Manager::Manager()
  { 
    renderer_ = nullptr; 
  }

  Manager::Manager(const IRenderer& renderer) :
    renderer_(&renderer)
  { }

  void Manager::update(const uint32_t dt)
  {
    for (auto s : systems_) {
      Entities entityList = getEntities(s->getType());
      s->update(dt, entityList);
    }
  }

  void Manager::render(const uint32_t dt)
  {
    if (renderer_) {
      renderer_->beforeRender();
    }
    for (auto s : systems_) {
      Entities entityList = getEntities(s->getType());
      s->render(dt, entityList);
    }
    if (renderer_) {
      renderer_->afterRender();
    }
  }

  void Manager::addEntity(Entity& entity)
  {
    auto entityTypes = entity.getComponentTypes();
    for (auto t : entityTypes) {
      auto systems = getSystems(t);
      for (auto s : systems) {
        s->onAddEntity(&entity);
      }
    }
    entities_.push_back(&entity);
  }

  Entity& Manager::createEntity(Components componentList)
  {
    Entity* e = new Entity(componentList);
    entities_.push_back(e);

    return *e;
  }

  void Manager::addSystem(System& system)
  {
    auto systemEntities = getEntities(system.getType());

    system.init(systemEntities);

    systems_.push_back(&system);
  }

  Systems& Manager::getSystems()
  {
    return systems_;
  }

  Systems Manager::getSystems(const std::string& systemType)
  {
    Systems systemList;

    for (auto s : systems_) {
      if (s->getType() == systemType) {
        systemList.push_back(s);  
      }
    }

    return systemList;
  }

  Entities& Manager::getEntities()
  {
    return entities_;
  }

  Entities Manager::getEntities(const std::string& comonentType)
  {
    Entities entityList;

    for (auto e : entities_) {
      if (e->hasComponent(comonentType)) {
        entityList.push_back(e);
      }
    }

    return entityList;
  }

}

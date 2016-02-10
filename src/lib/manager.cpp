
#include <initializer_list>
#include <iostream>
#include <set>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "entity.h"
#include "manager.h"

namespace aronnax {

  Manager::Manager() {
  }

  void Manager::update(const uint32_t dt)
  {
    for (auto s : systems_) {
      IEntities entityList = getEntities(s->getType());
      s->update(dt, entityList);
    }
  }

  void Manager::render(const uint32_t dt)
  {
    //renderer_.get()->beforeRender();
    for (auto s : systems_) {
      IEntities entityList = getEntities(s->getType());
      s->render(dt, entityList);
    }
    //renderer_.get()->afterRender();
  }

  void Manager::addEntity(IEntity& entity)
  {
    // for each entity component
    // // get component type
    // // for each system 
    // // // system->onAddEntity(entity)
    entities_.insert(&entity);
  }

  IEntity& Manager::createEntity(Components componentList)
  {
    Entity* e = new Entity(componentList);
    entities_.insert(e);

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

  IEntitySet& Manager::getEntities()
  {
    return entities_;
  }

  IEntities Manager::getEntities(const std::string& comonentType)
  {
    IEntities entityList;

    for (auto e : entities_) {
      if (e->hasComponent(comonentType)) {
        entityList.push_back(e);
      }
    }

    return entityList;
  }

}

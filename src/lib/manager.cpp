
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
      s->update(dt);
    }
  }

  void Manager::render(const uint32_t dt)
  {
    //renderer_.get()->beforeRender();
    for (auto s : systems_) {
      s->render(dt);
    }
    //renderer_.get()->afterRender();
  }

  void Manager::addEntity(IEntity& entity)
  {
    entities_.insert(&entity);
  }

  IEntity& Manager::createEntity(Components componentList)
  {
    Entity* e = new Entity(componentList);
    entities_.insert(e);

    return *e;
  }

  IEntitySet& Manager::getEntities()
  {
    return entities_;
  }

}

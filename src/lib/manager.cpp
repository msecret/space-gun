
#include <initializer_list>
#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "entity.h"
#include "events.h"
#include "manager.h"

namespace aronnax {

Manager::Manager(RendererPtr renderer):
  renderer_(renderer)
  { }

Manager::Manager(RendererPtr renderer, IEntities entities):
  entities_(entities),
  renderer_(renderer)
  { }

IEntityPtr Manager::add(Components componentList)
{
  std::cout << "in m component type: " << componentList[0]->getType() << "\n";
  EntityPtr entity = std::make_shared<Entity>(
      componentList, renderer_);
  entities_.insert(entity);

  return entity;
}

IEntities Manager::getEntities()
{
  return entities_;
}

void Manager::update(const uint32_t dt)
{
  for (auto e : entities_) {
    e->update(dt);
  }
}

void Manager::render()
{
  renderer_.get()->beforeRender();
  for (auto e : entities_) {
    e->render();
  }
  renderer_.get()->afterRender();

}

/*
void Manager::collision(const uint32_t dt)
{
  for (auto ea : collidableEntities_) {
    for (auto eb: collidableEntities_) {
      if (ea != eb) {
        ea.getComponent("collidable")->update(ea, eb, dt);
      }
    }
  }
}
*/

void Manager::event(const uint32_t dt)
{
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        SDL_Log("quit");
        exit(0);
        break;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        for (auto e : entities_) {
          if (e->hasComponent("Keyboardable")) {
            e->emit(EV_KEYBOARD, &event);
          }
        }
        break;

      default:
          break;
    }
  }
}

}

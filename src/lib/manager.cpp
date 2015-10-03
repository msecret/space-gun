
#include <initializer_list>
#include <iostream>
#include <stdio.h>

#include "SDL2/SDL.h"

#include "entity.h"
#include "manager.h"

namespace aronnax {

Manager::Manager(RendererPtr renderer):
  renderer_(renderer)
  { }

Manager::Manager(RendererPtr renderer, Entities entities):
  entities_(entities),
  renderer_(renderer)
  { }

EntityPtr Manager::add(Components componentList)
{
  std::cout << "in m component type: " << componentList[0]->getType() << "\n";
  EntityPtr entity = std::make_shared<aronnax::Entity>(
      componentList, renderer_);
  entities_.insert(entity);

  return entity;
}

void Manager::update(const uint32_t dt)
{
  for (auto e : entities_) {
    e->update(dt);
    //printf("e -> %f\n", e.get()->v.x);
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

void Manager::event(const uint32_t dt)
{
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    printf("poll1");
    SDL_Log("poll1ds");
    switch(event.type) {
      case SDL_QUIT:
        SDL_Log("quit");
        exit(0);
        break;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
        break;

      default:
          break;
    }
  }
}

}

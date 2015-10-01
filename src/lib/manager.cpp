
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

EntityPtr Manager::add(std::initializer_list<Component> components)
{
  Components componentList;
  for (auto component : components) {
    componentList.push_back(component);
  }

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

}

}

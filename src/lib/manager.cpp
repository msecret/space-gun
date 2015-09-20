
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

}

}

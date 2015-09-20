
#include "entity.h"
#include "manager.h"

namespace aronnax {

Manager::Manager(Entities entities):
  entities_(entities)
  { }

void Manager::update(const uint32_t dt)
{
  for (auto e : entities_) {
    e->update(dt);
  }
}

void Manager::render()
{

}

}


#ifndef _h_Manager
#define _h_Manager

#include <initializer_list>
#include <set>
#include <memory>

#include "entity.h"

namespace aronnax {

class Entity;
class Renderer;

typedef std::set<std::shared_ptr<Entity>> Entities;
// TODO does this need to be a ptr?
typedef std::shared_ptr<Renderer> RendererPtr;
typedef std::vector<Component> Components;

class Manager
{
  public:
    Manager(RendererPtr renderer);
    Manager(RendererPtr renderer, Entities entities);
    void update(const uint32_t dt);
    void render();
    // TODO use something besides init list here so you don't have {}.
    EntityPtr add(std::initializer_list<Component> components);

  private:
    Entities entities_;
    RendererPtr renderer_;

};

}

#endif


#ifndef _h_Manager
#define _h_Manager

#include <initializer_list>
#include <set>
#include <memory>

#include "component.h"
#include "entity.h"

namespace aronnax {

class Entity;
class Renderer;

typedef std::set<std::shared_ptr<Entity>> Entities;
// TODO does this need to be a ptr?
typedef std::shared_ptr<Renderer> RendererPtr;

class Manager
{
  public:
    Manager(RendererPtr renderer);
    Manager(RendererPtr renderer, Entities entities);
    void update(const uint32_t dt);
    void event(const uint32_t dt);
    //void collision(const uint32_t dt);
    void render();
    // TODO use something besides init list here so you don't have {}.
    EntityPtr add(Components components);

  private:
    Entities entities_;
    RendererPtr renderer_;

};

}

#endif

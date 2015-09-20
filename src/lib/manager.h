
#ifndef _h_Manager
#define _h_Manager

#include <set>
#include <memory>

namespace aronnax {

class Entity;
class Renderer;

typedef std::set<std::shared_ptr<Entity>> Entities;
typedef std::shared_ptr<Renderer> RendererPtr;
typedef std::vector<Component> Components;

class Manager
{
  public:
    Manager(RendererPtr renderer);
    Manager(RendererPtr renderer, Entities entities);
    void add(
    void update(const uint32_t dt);
    void render();

  private:
    Entities entities_;
    RendererPtr renderer_;

};

}

#endif

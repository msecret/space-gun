
#ifndef _h_Entity
#define _h_Entity

#include <memory>
#include <string>
#include <vector>


#include "component.h"
#include "event_emitter.h"
#include "renderer.h"
#include "units.h"

namespace aronnax {

typedef std::shared_ptr<Entity> EntityPtr;

class IEntity : public EventEmitter
{
  public:
    virtual void update(const uint32_t dt) = 0;
    virtual void render() = 0;
    virtual Renderer* getRenderer() = 0;
    virtual bool hasComponent(std::string componentType) = 0;
    virtual Component* getComponent(std::string componentType) = 0;
    Vector2d v;
    Vector2d pos;
    Vector2d box;
};

typedef std::shared_ptr<IEntity> IEntityPtr;

class Entity : public IEntity
{
  public:
    Entity(Components components);
    Entity(Components components,
           std::shared_ptr<Renderer> renderer);
    ~Entity() {};
    void update(const uint32_t dt);
    void render();
    Renderer* getRenderer();
    Vector2d v;
    Vector2d pos;
    Vector2d box;
    bool hasComponent(std::string componentType);
    Component* getComponent(std::string componentType);

  private:
    // TODO typedef replace all of these
    Components components_;
    std::shared_ptr<aronnax::Renderer> renderer_;

};

}

#endif

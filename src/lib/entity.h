
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
    virtual ~IEntity(){};
    virtual void update(const uint32_t dt) = 0;
    virtual void render() = 0;
    virtual Renderer* getRenderer() = 0;
    virtual bool hasComponent(std::string componentType) = 0;
    virtual Component* getComponent(std::string componentType) = 0;
    virtual void setPos(Vector2d pos) = 0;
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
    bool hasComponent(std::string componentType);
    Component* getComponent(std::string componentType);
    Vector2d getPos();
    void setPos(Vector2d pos);

  private:
    // TODO typedef replace all of these
    Components components_;
    std::shared_ptr<aronnax::Renderer> renderer_;
    Vector2d pos;

};

}

#endif

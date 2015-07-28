
#ifndef _h_Component
#define _h_Component

class Entity;

class Component
{
  public:
    virtual ~Component() {}
    virtual void receive(int message) = 0;
    virtual void update(Entity& entity, int dt) = 0;
};

#endif

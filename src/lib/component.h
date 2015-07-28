
#ifndef _h_Component
#define _h_Component

class Entity;

class Component
{
  public:
    void receive(int message);
    void update(Entity& entity, int dt);
};

#endif

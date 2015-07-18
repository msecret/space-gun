
#ifndef _h_Component
#define _h_Component

class Component
{
  public:
    virtual ~Component() {}
    virtual void receive(int message) = 0;
    virtual void update(int dt) = 0;
};

#endif

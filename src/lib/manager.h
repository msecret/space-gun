
#ifndef _h_Manager
#define _h_Manager

#include <set>
#include <memory>

namespace aronnax {

class Entity;

typedef std::set<std::shared_ptr<Entity>> Entities;

class Manager
{
  public:
    Manager(Entities);
    void update(const uint32_t dt);
    void render();

  private:
    Entities entities_;

};

}

#endif

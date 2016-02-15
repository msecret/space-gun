
#ifndef _h_System
#define _h_System

#include <cstdint>
#include <string>
#include <vector>

#include "component.h"
#include "entity.h"

namespace aronnax {
  using namespace std;

  extern const string COMPONENT_TYPE_BASE;

  class System
  {
    public:
      virtual ~System() {};
      virtual void init(Entities& entities) {};
      virtual void update(const uint32_t dt, Entities& entities) {};
      virtual void render(const uint32_t dt, Entities& entities) {};
      virtual void onAddEntity(Entity& entity) {};
      virtual const string& getType() { return COMPONENT_TYPE_BASE; };
  };

  using Systems = vector<System*>;
}

#endif

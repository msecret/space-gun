
#ifndef _h_Death
#define _h_Death

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"
#include "lib/units.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::System;

  class Death: public System
  {
    public:
      Death() {};
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities) {};
      void onAddEntity(Entity& entity);
      const string& getType();

    private:
      void bindEntity(Entity& entity);
      void resetEntity(Entity& entity);

  };
}

#endif

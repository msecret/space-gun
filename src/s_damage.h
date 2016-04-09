
#ifndef _h_Damage
#define _h_Damage

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"
#include "lib/units.h"

namespace spacegun {
  using std::string;
  using aronnax::EV_IMPACT;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvImpact;
  using aronnax::System;

  class Damage: public System
  {
    public:
      Damage(){ }
      void init(Entities& entities) {};
      void update(const uint32_t dt, Entities& entities);
      void render(const uint32_t dt, Entities& entities) {};
      void onAddEntity(Entity& entity) {};
      const string& getType();

    private:
      bool checkHealth(Entity& entity);
      void emitIfDead(Entity& entity);
  };
}

#endif

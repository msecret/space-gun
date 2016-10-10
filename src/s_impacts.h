
#ifndef _h_Impacts
#define _h_Impacts

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

  class Impacts: public aronnax::System
  {
    public:
      Impacts() {};
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities) {};
      void onAddEntity(Entity& entity);
      const string& getType();

    private:
      void bindEntity(Entity& entity);
      void handleImpact(Entity& entity, EvImpact& ev);
      void handleDeath(Entity& entity);

  };
}

#endif


#ifndef _h_Arm
#define _h_Arm

#include <cstdint>

#include "lib/entity.h"
#include "lib/units.h"
#include "lib/system.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::EvWeaponFired;

  class Arm: public aronnax::System
  {
    public:
      Arm() {};
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities) {};
      void onAddEntity(Entity& entity);
      const string& getType();

    private:
      void bindEntity(Entity& e);
      void activateWeapon(EvWeaponFired& ev, Entity& entity);

  };
}

#endif


#ifndef _h_Thrust
#define _h_Thrust

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;

  class Thrust: public aronnax::System
  {
    public:
      Thrust() {};
      void init(aronnax::Entities& entities);
      void update(const uint32_t dt, aronnax::Entities& entities) {};
      void render(const uint32_t dt, aronnax::Entities& entities) {};
      void onAddEntity(aronnax::Entity& entity);
      const string& getType();

    private:
      void bindEntity(aronnax::Entity& entity);
      void handleKeys(aronnax::EvUserMovement& ev,
          aronnax::Entity& entity);

  };
}

#endif
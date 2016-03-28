
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
      void handleMovementKey(aronnax::EvUserMovement& ev,
          aronnax::Entity& entity);
      void handleRotationKey(aronnax::EvUserRotation& ev,
          aronnax::Entity& entity);
      Vector2d getForce(Vector2d direction, float angle);

  };
}

#endif

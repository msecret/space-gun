
#ifndef _h_Bound
#define _h_Bound

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;

  class Bound: public aronnax::System
  {
    public:
      Bound() {};
      void init(aronnax::Entities& entities) {};
      void update(const uint32_t dt, aronnax::Entities& entities);
      void render(const uint32_t dt, aronnax::Entities& entities) {};
      void onAddEntity(aronnax::Entity& entity) {};
      const string& getType();

    private:
      void checkBounds(const uint32_t dt, aronnax::Entity& entity);
      float wrapAround(float coordinate, float max);

  };
}

#endif

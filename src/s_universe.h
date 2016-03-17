
#ifndef _h_Universe
#define _h_Universe

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;
  using aronnax::Entity;
  using aronnax::Entities;

  class Universe: public aronnax::System
  {
    public:
      Universe() {};
      void init(Entities& entities) {};
      void update(const uint32_t dt, Entities& entities);
      void render(const uint32_t dt, Entities& entities) {};
      void onAddEntity(Entity& entity) {};
      const string& getType();

    private:
      void updateWorld(const uint32_t dt, Entity& entity);

  };
}

#endif

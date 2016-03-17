
#ifndef _h_Movement
#define _h_Movement

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;
  using aronnax::Entities;

  class Movement: public aronnax::System
  {
    public:
      Movement() {};
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities) {};
      void onAddEntity(Entity& entity);
      const string& getType();

    private:
      void bindEntity(Entity& entity);

  };
}

#endif

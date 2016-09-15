
#ifndef _h_Joints
#define _h_Joints

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;

  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::System;

  class Joints: public System
  {
    public:
      Joints() {};
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities) {};
      void onAddEntity(Entity& entity);
      const string& getType();

    private:
      void initEntity(Entity& entity);
      void bindEntity(Entity& parentEntity, Entity& childEntity);

  };
}

#endif


#ifndef _h_Joints
#define _h_Joints

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"

namespace spacegun {
  using namespace std;

  class Joints: public aronnax::System
  {
    public:
      Joints() {};
      void init(aronnax::Entities& entities);
      void update(const uint32_t dt, aronnax::Entities& entities) {};
      void render(const uint32_t dt, aronnax::Entities& entities) {};
      void onAddEntity(aronnax::Entity& entity);
      const string& getType();

    private:
      void bindEntity(aronnax::Entity& entity);

  };
}

#endif

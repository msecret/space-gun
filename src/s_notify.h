
#ifndef _h_Notify
#define _h_Notify

#include <cstdint>

#include "lib/entity.h"
#include "lib/system.h"
#include "lib/units.h"

namespace spacegun {
  using std::string;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::System;

  class Notify: public System
  {
    public:
      Notify() :
        renderer_(nullptr)
      { }
      Notify(IRenderer* renderer) :
        renderer_(renderer)
      { }
      void init(Entities& entities) {};
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities);
      void onAddEntity(Entity& entity) {};
      const string& getType();

    private:
      void writeText(Entity& entity);
      IRenderer* renderer_;

  };
}

#endif

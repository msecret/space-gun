
#ifndef _h_RetcangleRenderer
#define _h_RectangleRenderer

#include <cstdint>

#include "lib/entity.h"
#include "lib/renderer.h"
#include "lib/system.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::System;

  class RectangleRenderer: public System
  {
    public:
      RectangleRenderer();
      RectangleRenderer(IRenderer* renderer);
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities);
      void onAddEntity(Entity& entity) {};
      const string& getType();

    private:
      IRenderer* renderer_;
      void renderRectangle(const uint32_t dt, Entity&);
      void initRectangle(Entity&);

  };
}

#endif

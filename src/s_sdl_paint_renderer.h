
#ifndef _h_SDLPaintRenderer
#define _h_SDLPaintRenderer

#include <cstdint>

#include "lib/entity.h"
#include "lib/sdl_renderer.h"
#include "lib/system.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Entity;
  using aronnax::Entities;
  using aronnax::SDLRenderer;
  using aronnax::System;

  class SDLPaintRenderer: public System
  {
    public:
      SDLPaintRenderer();
      SDLPaintRenderer(SDLRenderer* renderer);
      void init(Entities& entities);
      void update(const uint32_t dt, Entities& entities) {};
      void render(const uint32_t dt, Entities& entities);
      void onAddEntity(Entity& entity) {};
      const string& getType();

    private:
      SDLRenderer* renderer_;
      void renderRectangle(const uint32_t dt, Entity&);
      void initRectangle(Entity&);

  };
}

#endif


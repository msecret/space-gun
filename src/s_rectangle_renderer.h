
#ifndef _h_RetcangleRenderer
#define _h_RectangleRenderer

#include <cstdint>

#include "lib/entity.h"
#include "lib/renderer.h"
#include "lib/system.h"

namespace spacegun {
  using namespace aronnax;
  using namespace std;
  
  class RectangleRenderer: public aronnax::System 
  {
    public:
      RectangleRenderer();
      RectangleRenderer(IRenderer* renderer);
      void init(aronnax::Entities& entities) {};
      void update(const uint32_t dt, aronnax::Entities& entities) {};
      void render(const uint32_t dt, aronnax::Entities& entities);
      void onAddEntity(aronnax::Entity& entity) {};
      const string& getType();
      
    private:
      IRenderer* renderer_;
      void renderRectangle(const uint32_t dt, aronnax::Entity&);

  };
}

#endif

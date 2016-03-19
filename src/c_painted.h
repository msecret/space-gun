
#ifndef _h_Painted
#define _h_Painted

#include <cstdint>
#include <string>

#include <SDL2/SDL.h>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using std::string;
  using aronnax::Color;
  using aronnax::Component;

  const string COMPONENT_TYPE_PAINTED = "painted";

  class Painted: public Component
  {
    public:
      Painted();
      Painted(const Color& c);
      Painted(const uint8_t r,
              const uint8_t g,
              const uint8_t b,
              const uint8_t a);
      const string getType();
      const Color& getColor();
      void setColor(const Color& color);
      SDL_Texture* getTexture();
      //void initTexture(float width, float height);

    private:
      Color color_;
      SDL_Texture* texture_;
      //SDL_Texture* createTexture(const Color& color);

  };
}

#endif

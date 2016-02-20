
#ifndef _h_Painted
#define _h_Painted

#include <cstdint>
#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_PAINTED = "painted";

  class Painted: public aronnax::Component
  {
    public:
      Painted();
      Painted(const aronnax::Color& c);
      Painted(const uint8_t r,
              const uint8_t g,
              const uint8_t b,
              const uint8_t a);
      const string getType();
      const aronnax::Color& getColor();
      void setColor(const aronnax::Color& color);

    private:
      aronnax::Color color_;

  };
}

#endif

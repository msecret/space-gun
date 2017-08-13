
#ifndef _h_BaseShaped
#define _h_BaseShaped

#include <cstdint>
#include <string>

#include "lib/component.h"
#include "lib/units.h"

#include "alias.h"

namespace spacegun {
  using std::string;
  using aronnax::Component;

  const string COMPONENT_TYPE_BASE_SHAPED = "baseshaped";

  class BaseShaped: public aronnax::Component
  {
    public:
      virtual ~BaseShaped() {};
      virtual const string getType() { return COMPONENT_TYPE_BASE_SHAPED; };
      virtual b2Shape* getShape() = 0;
      virtual Vector2d getBoundingBox() = 0;
  };
}

#endif

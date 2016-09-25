
#ifndef _h_Shaped
#define _h_Shaped

#include <cstdint>
#include <string>

#include "lib/component.h"
#include "lib/units.h"

#include "c_base_shaped.h"

namespace spacegun {
  using std::string;
  using aronnax::Component;

  const string COMPONENT_TYPE_SHAPED = "shaped";

  class Shaped: public aronnax::Component
  {
    public:
      Shaped(BaseShaped& shapeComponent) :
        shapeComponent_(&shapeComponent)
      {};
      const string getType();
      const string getShapeType();
      BaseShaped* getShapeComponent();
      Shape* getShape();
      Vector2d getBoundingBox();

    private:
      BaseShaped* shapeComponent_;
  };
}

#endif

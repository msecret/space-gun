
#ifndef _h_Shaped
#define _h_Shaped

#include <cstdint>
#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using std::string;
  using aronnax::Component;

  const string COMPONENT_TYPE_SHAPED = "shaped";

  template <class TShape>
  class Shaped: public aronnax::Component
  {
    public:
      Shaped(TShape& shapeComponent) :
        shapeComponent_(&shapeComponent)
      {};
      const string getType();
      const string getShapeType();
      TShape* getShapeComponent();
      Shape* getShape();

    private:
      TShape* shapeComponent_;
  };
}

#endif

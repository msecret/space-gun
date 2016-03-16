
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

  class Shaped: public aronnax::Component
  {
    public:
      Shaped(Component& shapeComponent) :
        shapeComponent_(&shapeComponent)
      {};
      const string getType();
      const string getShapeType();
      //Component* getShape();

    private:
      Component* shapeComponent_;
  };
}

#endif

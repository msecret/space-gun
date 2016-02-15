
#ifndef _h_Boundable
#define _h_Boundable

#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_BOUNDABLE = "boundable";

  class Boundable : public aronnax::Component
  {
    public:
      Boundable() {};
      Boundable(const aronnax::Vector2d& worldMax)
        : bounds_(worldMax) {};
      const string getType();
      const aronnax::Vector2d& getBounds();


    private:
      aronnax::Vector2d bounds_;
  };

}

#endif

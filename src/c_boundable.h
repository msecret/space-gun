
#ifndef _h_Boundable
#define _h_Boundable

#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;
  using namespace aronnax;

  const string COMPONENT_TYPE_BOUNDABLE = "boundable";

  class Boundable : public aronnax::Component
  {
    public:
      Boundable() {};
      Boundable(const Vector2d& worldMax)
        : bounds_(worldMax) {};
      const string getType();
      const Vector2d& getBounds();


    private:
      Vector2d bounds_;
  };

}

#endif

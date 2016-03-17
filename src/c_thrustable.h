
#ifndef _h_Thrustable
#define _h_Thrustable

#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_THRUSTABLE = "thrustable";

  class Thrustable : public aronnax::Component
  {
    public:
      Thrustable()
        : factor_(0) { };
      Thrustable(float factor)
        : factor_(factor) {};
      const string getType();
      float getFactor();
      void setFactor(float factor);


    private:
      float factor_;
  };

}

#endif

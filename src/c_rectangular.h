
#ifndef _h_Rectangular
#define _h_Rectangular

#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_RECTANGULAR = "rectangular";

  class Rectangular : public aronnax::Component
  {
    public:
      Rectangular() {};
      Rectangular(float w, float h);
      const string getType();
      float getW();
      float getH();
      void setW(float w);
      void setH(float h);

    private:
      aronnax::Vector2d box_;
  };

}

#endif

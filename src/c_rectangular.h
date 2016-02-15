
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
      Rectangular(double w, double h);
      const string getType();
      double getW();
      double getH();
      void setW(double w);
      void setH(double h);

    private:
      aronnax::Vector2d box_;
  };

}

#endif

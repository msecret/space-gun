
#ifndef _h_Thrustable
#define _h_Thrustable

#include <array>
#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_THRUSTABLE = "thrustable";

  const array<float, 4> defaultDirectionalFactors = { 1.0f, 1.0f, 1.0f, 1.0f };
  const bool DEFAULT_ORIENTED_STRAFE = true;

  class Thrustable : public aronnax::Component
  {
    public:
      Thrustable() :
        factor_(0),
        directionFactors_(defaultDirectionalFactors),
        isOrientedStrafe_(DEFAULT_ORIENTED_STRAFE)
      { }
      Thrustable(float factor) :
        factor_(factor),
        directionFactors_(defaultDirectionalFactors),
        isOrientedStrafe_(DEFAULT_ORIENTED_STRAFE)
      { }
      Thrustable(float factor, bool isOrientedStrafe) :
        factor_(factor),
        directionFactors_(defaultDirectionalFactors),
        isOrientedStrafe_(isOrientedStrafe)
      { }
      const string getType();
      float getFactor();
      void setFactor(float factor);
      void setUpFactor(float up);
      void setDownFactor(float down);
      float getUpFactor();
      float getDownFactor();
      void setRightFactor(float right);
      void setLeftFactor(float left);
      float getRightFactor();
      float getLeftFactor();
      bool isOrientedStrafe();


    private:
      float factor_;
      array<float, 4> directionFactors_;
      bool isOrientedStrafe_;
  };

}

#endif

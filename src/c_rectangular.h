
#ifndef _h_Rectangular
#define _h_Rectangular

#include <string>

#include <Box2D/Box2D.h>

#include "alias.h"
#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  using aronnax::Vector2d;

  const string COMPONENT_TYPE_RECTANGULAR = "rectangular";

  class Rectangular : public aronnax::Component
  {
    public:
      Rectangular() :
        shape_(new PolygonShape)
      {};
      Rectangular(float w, float h);
      ~Rectangular();
      const string getType();
      float getW();
      float getH();
      void setW(float w);
      void setH(float h);
      PolygonShape* getShape();

    private:
      Vector2d box_;
      PolygonShape* shape_;
  };

}

#endif

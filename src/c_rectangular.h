
#ifndef _h_Rectangular
#define _h_Rectangular

#include <string>

#include <Box2D/Box2D.h>

#include "lib/component.h"
#include "lib/units.h"

#include "alias.h"
#include "c_base_shaped.h"

namespace spacegun {
  using namespace std;

  using aronnax::Vector2d;

  const string COMPONENT_TYPE_RECTANGULAR = "rectangular";

  class Rectangular : public BaseShaped
  {
    public:
      Rectangular() :
        shape_(new PolygonShape)
      {};
      Rectangular(float w, float h);
      ~Rectangular();
      const string getType();
      PolygonShape* getShape();
      Vector2d getBoundingBox();
      float getW();
      float getH();
      void setW(float w);
      void setH(float h);

    private:
      Vector2d box_;
      PolygonShape* shape_;
  };

}

#endif

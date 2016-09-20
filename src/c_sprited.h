
#ifndef _h_Sprited
#define _h_Sprited

#include <string>

#include <Box2D/Box2D.h>

#include "lib/component.h"
#include "lib/entity.h"
#include "lib/units.h"

#include "alias.h"

namespace spacegun {
  using std::string;
  using aronnax::Component;
  using aronnax::Entity;
  using aronnax::Vector2d;

  const string COMPONENT_TYPE_SPRITED = "sprited";

  class Sprited: public Component
  {
    public:
      Sprited(string filePath) :
        filePath_(filePath) {};
      const string getType();
      const string& getFilePath();

    private:
      string filePath_;
  };
}

#endif

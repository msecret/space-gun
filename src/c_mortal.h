
#ifndef _h_Mortal
#define _h_Mortal

#include <cstdint>
#include <string>

#include "lib/component.h"
#include "lib/units.h"

#include "c_base_shaped.h"

namespace spacegun {
  using std::string;
  using aronnax::Component;

  const string COMPONENT_TYPE_MORTAL = "mortal";

  class Mortal: public Component
  {
    public:
      Mortal() :
        deaths_(0),
        notificationLine(-1)
      {}
      const string getType();
      void addDeath();
      int getDeaths();
      int notificationLine;

    private:
      int deaths_;
  };
}

#endif

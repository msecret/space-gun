
#ifndef _h_Hideable
#define _h_Hideable

#include <string>

#include "lib/component.h"

#include "alias.h"

namespace spacegun {
  using std::string;
  using aronnax::Component;

  const string COMPONENT_TYPE_HIDEABLE = "hideable";

  class Hideable: public Component
  {
    public:
      Hideable(bool defaultHidden=false) :
        hidden_(defaultHidden)
      { }
      bool getHidden();
      void setHidden(bool hidden);
      const string getType();

    private:
      bool hidden_;
  };
}

#endif

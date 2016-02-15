
#ifndef _h_Component
#define _h_Component

#include <cstdint>
#include <string>
#include <vector>

namespace aronnax {
  using namespace std;

  const string COMPONENT_TYPE_BASE = "base";

  class Component
  {
    public:
      virtual ~Component() {};
      virtual const string getType() { return COMPONENT_TYPE_BASE; };
  };

  using Components = vector<Component*>;

}

#endif

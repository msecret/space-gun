
#ifndef _h_Component
#define _h_Component

#include <cstdint>
#include <string>
#include <vector>

namespace aronnax {

  const std::string COMPONENT_TYPE_BASE = "base";

  class Component
  {
    public:
      virtual ~Component() {};
      virtual std::string getType() { return COMPONENT_TYPE_BASE; };
  };

  using Components = std::vector<Component*>;

}

#endif


#include "c_hideable.h"

namespace spacegun {
  using std::string;

  extern const string COMPONENT_TYPE_HIDEABLE;

  bool Hideable::getHidden() {
    return hidden_;
  }

  void Hideable::setHidden(bool hidden) {
    hidden_ = hidden;
  }

  const string Hideable::getType()
  {
    return COMPONENT_TYPE_HIDEABLE;
  }
}
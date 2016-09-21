
#include <string>

#include "c_sprited.h"

namespace spacegun {
  using std::string;

  extern const string COMPONENT_TYPE_SPRITED;

  const string Sprited::getType()
  {
    return COMPONENT_TYPE_SPRITED;
  }

  const string& Sprited::getFilePath()
  {
    return filePath_;
  }
}

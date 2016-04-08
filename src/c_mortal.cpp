
#include <string>

#include "lib/units.h"

#include "c_mortal.h"

namespace spacegun {
  using std::string;

  extern const string COMPONENT_TYPE_MORTAL;

  const string Mortal::getType()
  {
    return COMPONENT_TYPE_MORTAL;
  }

  void Mortal::addDeath()
  {
    deaths_ += 1;
  }

  int Mortal::getDeaths()
  {
    return deaths_;
  }
}

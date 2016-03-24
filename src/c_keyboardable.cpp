
#include <map>
#include <string>

#include "lib/units.h"

#include "c_keyboardable.h"


namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_KEYBOARDABLE;


  Keyboardable::Keyboardable() :
    keyMap_()
  { }

  Keyboardable::Keyboardable(map<string, aronnax::Ev*>& keyMap) :
    keyMap_(keyMap)
  { }

  const string Keyboardable::getType()
  {
    return COMPONENT_TYPE_KEYBOARDABLE;
  }

  vector<string> Keyboardable::getKeys()
  {
    vector<string> keys;
    for(auto key : keyMap_) {
      keys.push_back(key.first);
    }

    return keys;
  }
}

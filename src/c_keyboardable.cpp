
#include <map>
#include <string>

#include "c_keyboardable.h"


namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_KEYBOARDABLE;


  map<const string, const unsigned int> DEFAULT_CONTROLS;

  Keyboardable::Keyboardable() :
    keyMap_()
  { }

  Keyboardable::Keyboardable(map<string, unsigned int> keyMap) :
    keyMap_(keyMap)
  { }

  const string Keyboardable::getType()
  {
    return COMPONENT_TYPE_KEYBOARDABLE;
  }

  vector<string> Keyboardable::getKeys()
  {
    vector<string> keys;
    for(auto key : keyMap_)
      keys.push_back(key.first);

    return keys;
  }

  unsigned int Keyboardable::getAction(const string& key)
  {
    return keyMap_[key];
  }
}


#include <map>
#include <string>

#include "c_keyboardable.h"


namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_KEYBOARDABLE;

  extern const unsigned int EV_MOVEMENT;
  extern const unsigned int EV_MOVEMENT_UP;
  extern const unsigned int EV_MOVEMENT_DOWN;
  extern const unsigned int EV_MOVEMENT_RIGHT;
  extern const unsigned int EV_MOVEMENT_LEFT;

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

  unsigned int Keyboardable::getMovement(const string& key)
  {
    return keyMap_[key];
  }
}

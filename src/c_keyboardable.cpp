
#include <map>
#include <string>

#include "lib/units.h"

#include "c_keyboardable.h"


namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_KEYBOARDABLE;


  Keyboardable::Keyboardable(const unsigned int eventCode) :
    eventCode(eventCode),
    keyMap_()
  { }

  Keyboardable::Keyboardable(const unsigned int eventCode,
      map<string, aronnax::Ev*>& keyMap) :
    eventCode(eventCode),
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

  const unsigned int Keyboardable::getEventCode()
  {
    return eventCode;
  }

}

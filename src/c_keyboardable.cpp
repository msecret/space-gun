
#include <map>
#include <string>

#include "c_keyboardable.h"


namespace spacegun {
  using namespace std;

  extern const string COMPONENT_TYPE_KEYBOARDABLE;


  Keyboardable::Keyboardable(const unsigned int eventCode) :
    eventCode(eventCode),
    keyMap_()
  { }

  Keyboardable::Keyboardable(const unsigned int eventCode,
      const map<string, aronnax::Ev*>& keyMap) :
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
    for(auto key : keyMap_)
      keys.push_back(key.first);

    return keys;
  }

  const unsigned int Keyboardable::getEventCode()
  {
    return eventCode;
  }

  const aronnax::Ev* Keyboardable::getAction(const string& key)
  {
    aronnax::Ev* action = nullptr;
    if (keyMap_.find(key) != keyMap_.end()) {
      action = keyMap_.at(key);
    }

    return action;
  }
}

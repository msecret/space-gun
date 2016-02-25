
#ifndef _h_Keyboardable
#define _h_Keyboardable

#include <map>
#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_KEYBOARDABLE = "keyboardable";

  const unsigned int EV_MOVEMENT = 100;
  const unsigned int EV_MOVEMENT_UP = 101;
  const unsigned int EV_MOVEMENT_DOWN = 102;
  const unsigned int EV_MOVEMENT_RIGHT = 103;
  const unsigned int EV_MOVEMENT_LEFT = 104;

  class Keyboardable : public aronnax::Component
  {
    public:
      Keyboardable();
      Keyboardable(map<string, unsigned int> keyMap);
      const string getType();
      vector<string> getKeys();
      unsigned int getMovement(const string& key);

    private:
      map<string, unsigned int> keyMap_;

  };
}

#endif


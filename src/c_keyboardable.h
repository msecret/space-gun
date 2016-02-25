
#ifndef _h_Keyboardable
#define _h_Keyboardable

#include <map>
#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;

  const string COMPONENT_TYPE_KEYBOARDABLE = "keyboardable";

  class Keyboardable : public aronnax::Component
  {
    public:
      Keyboardable();
      Keyboardable(map<string, unsigned int> keyMap);
      const string getType();
      vector<string> getKeys();
      unsigned int getAction(const string& key);

    private:
      map<string, unsigned int> keyMap_;

  };
}

#endif



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
      Keyboardable(const unsigned int eventCode);
      Keyboardable(const unsigned int eventCode,
          const map<string, aronnax::Ev*>& keyMap);
      const string getType();
      vector<string> getKeys();
      const unsigned int getEventCode();
      const aronnax::Ev* getAction(const string& key);

    private:
      const unsigned int eventCode;
      const map<string, aronnax::Ev*> keyMap_;

  };
}

#endif


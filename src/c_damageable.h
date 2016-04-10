
#ifndef _h_Damageable
#define _h_Damageable

#include <string>

#include "lib/component.h"
#include "lib/units.h"

namespace spacegun {
  using namespace std;
  using namespace aronnax;

  const string COMPONENT_TYPE_DAMAGEABLE = "damageable";

  class Damageable : public aronnax::Component {
    public:
      Damageable(float health=0);
      const string getType();
      float getHealth();
      void applyDamage(float damage);
      void setDamageFactor(float factor);
      void resetHealth();
      int notificationLine;

    private:
      float health_;
      float initialHealth_;
      float factor_;
  };

}

#endif

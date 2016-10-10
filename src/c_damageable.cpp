
#include <cstdio>
#include <iostream>
#include <iostream>

#include "c_damageable.h"

namespace spacegun {

  extern const string COMPONENT_TYPE_DAMAGEABLE;

  Damageable::Damageable(float health) :
    notificationLine(-1)
  {
    initialHealth_ = health;
    health_ = health;
  }

  const string Damageable::getType()
  {
    return COMPONENT_TYPE_DAMAGEABLE;
  }

  float Damageable::getHealth()
  {
    return health_;
  }

  void Damageable::applyDamage(float damage)
  {
    float total = damage * factor_;
    health_ -= total;
  }

  void Damageable::setDamageFactor(float factor)
  {
    factor_ = factor;
  }

  void Damageable::resetHealth()
  {
    using std::cout;
    using std::endl;
    cout << "reset" << endl;
    health_ = initialHealth_;
  }

}


#include <iostream>

#include "c_damageable.h"

namespace spacegun {

  extern const string COMPONENT_TYPE_DAMAGEABLE;

  Damageable::Damageable(float health)
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
    using std::cout;
    using std::endl;
    cout << "health: " << health_ << endl;
  }

  void Damageable::setDamageFactor(float factor)
  {
    factor_ = factor;
  }

}

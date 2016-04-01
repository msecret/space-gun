
#include <gtest/gtest.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_damageable.h"
#include "../s_impacts.h"

using std::vector;
using namespace spacegun;

TEST(Impacts, onAddEntity) {
  vector<float> impulses;
  float expectedA = 2.0f;
  float expectedB = 2.5f;
  float expected = 100 - expectedA - expectedB;
  impulses.push_back(expectedA);
  impulses.push_back(expectedB);
  EvImpact ev(impulses);

  Damageable c(100);
  auto e = new Entity();
  e->addComponent(&c);

  Impacts s;
  s.onAddEntity(*e);

  e->emit(EV_IMPACT, &ev);

  auto actual = c.getHealth();

  EXPECT_FLOAT_EQ(actual, expected);

  delete e;
}

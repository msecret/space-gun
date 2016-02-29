
#include <map>
#include <string>

#include <gtest/gtest.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_keyboardable.h"
#include "../s_keyboard_events.h"

using namespace std;
using namespace spacegun;

TEST(Keyboardable, Constructor) {
  aronnax::Ev expected;
  unsigned int expectedCode = 32;
  map<string, aronnax::Ev*> keyMap;
  keyMap["testa"] = &expected;

  Keyboardable c = Keyboardable(expectedCode, keyMap);

  auto actual = c.getAction("testa");

  EXPECT_EQ(&expected, actual);
  EXPECT_EQ(c.getEventCode(), expectedCode);
}

TEST(Keyboardable, getType) {
  Keyboardable c(100);

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_KEYBOARDABLE);
}

TEST(Keyboardable, getKeys) {
  unsigned int expectedCode = 33;
  aronnax::Ev eva;
  aronnax::Ev evb;
  map<string, aronnax::Ev*> keyMap;
  string expectedA = "testa";
  string expectedB = "testb";
  keyMap[expectedA] = &eva;
  keyMap[expectedB] = &evb;

  Keyboardable c = Keyboardable(expectedCode, keyMap);

  // TODO do maps in c++ guarantee an order?
  auto actualA = c.getKeys().at(0);
  auto actualB = c.getKeys().at(1);

  EXPECT_EQ(expectedA, actualA);
  EXPECT_EQ(expectedB, actualB);
}

TEST(Keyboardable, getAction) {
  unsigned int expectedCode = 34;
  aronnax::Ev expectedA;
  aronnax::Ev expectedB;
  map<string, aronnax::Ev*> keyMap;
  keyMap["testa"] = &expectedA;
  keyMap["testb"] = &expectedB;

  Keyboardable c = Keyboardable(expectedCode, keyMap);

  auto actualA = c.getAction("testa");
  auto actualB = c.getAction("testb");

  EXPECT_EQ(&expectedA, actualA);
  EXPECT_EQ(&expectedB, actualB);
}

TEST(KeyboardEvents, getType) {
  KeyboardEvents<aronnax::Ev> s;

  auto actual = s.getType();

  EXPECT_EQ(COMPONENT_TYPE_KEYBOARDABLE, actual);
}


TEST(KeyboardEvents, onAddEntity) {
  const unsigned int EV_USER_MOVEMENT = 9999;
  aronnax::Vector2d up = { 0, -1 };
  aronnax::Vector2d down = { 0, 1 };
  aronnax::EvUserMovement* evUp = new aronnax::EvUserMovement(up);
  aronnax::EvUserMovement* evDown = new aronnax::EvUserMovement(down);
  map<string, aronnax::Ev*> keyMap;
  keyMap["A"] = evUp;
  keyMap["S"] = evDown;
  aronnax::EvKeyboard ev("A", aronnax::EvKeyState::STATE_UP);

  auto c = Keyboardable(EV_USER_MOVEMENT, keyMap);
  aronnax::Entity* e = new aronnax::Entity();
  e->addComponent(&c);

  auto s = KeyboardEvents<aronnax::EvUserMovement>();
  s.onAddEntity(*e);

  e->on(EV_USER_MOVEMENT, [&](const aronnax::EvUserMovement* ev) {

  });

  e->emit(aronnax::EV_KEY, &ev);
}

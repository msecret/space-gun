
#include <map>
#include <string>

#include <gtest/gtest.h>

#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_keyboardable.h"
#include "../s_keyboard_events.h"


using namespace std;

using aronnax::EV;
using aronnax::EV_USER_MOVEMENT;
using aronnax::Ev;
using aronnax::EvUserMovement;
using aronnax::Vector2d;

using namespace spacegun;

TEST(Keyboardable, Constructor) {
  Ev expected;
  map<string, aronnax::Ev*> keyMap;
  keyMap["testa"] = &expected;

  Keyboardable c = Keyboardable(keyMap);

  auto actual = c.getAction<Ev>("testa");

  EXPECT_EQ(&expected, actual);
}

TEST(Keyboardable, getType) {
  Keyboardable c;

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_KEYBOARDABLE);
}

TEST(Keyboardable, getKeys) {
  Ev eva;
  Ev evb;
  map<string, Ev*> keyMap;
  string expectedA = "testa";
  string expectedB = "testb";
  keyMap[expectedA] = &eva;
  keyMap[expectedB] = &evb;

  Keyboardable c = Keyboardable(keyMap);

  // TODO do maps in c++ guarantee an order?
  auto actualA = c.getKeys().at(0);
  auto actualB = c.getKeys().at(1);

  EXPECT_EQ(expectedA, actualA);
  EXPECT_EQ(expectedB, actualB);
}

TEST(Keyboardable, getAction) {
  aronnax::Ev expectedA;
  aronnax::Ev expectedB;
  map<string, aronnax::Ev*> keyMap;
  keyMap["testa"] = &expectedA;
  keyMap["testb"] = &expectedB;

  Keyboardable c = Keyboardable(keyMap);

  auto actualA = c.getAction<aronnax::Ev>("testa");
  auto actualB = c.getAction<aronnax::Ev>("testb");
  auto actualCode = actualA->getEventCode();

  EXPECT_EQ(&expectedA, actualA);
  EXPECT_EQ(&expectedB, actualB);
  EXPECT_EQ(actualCode, EV);
}

TEST(KeyboardEvents, getType) {
  KeyboardEvents<aronnax::Ev> s;

  auto actual = s.getType();

  EXPECT_EQ(COMPONENT_TYPE_KEYBOARDABLE, actual);
}


TEST(KeyboardEvents, onAddEntity) {
  Vector2d up = { 0, -1 };
  Vector2d down = { 0, 1 };
  aronnax::EvUserMovement* evUp = new aronnax::EvUserMovement(up);
  aronnax::EvUserMovement* evDown = new aronnax::EvUserMovement(down);
  map<string, aronnax::Ev*> keyMap;
  keyMap["A"] = evUp;
  keyMap["S"] = evDown;
  aronnax::EvKeyboard ev("A", aronnax::EvKeyState::STATE_UP);

  auto c = Keyboardable(keyMap);
  aronnax::Entity* e = new aronnax::Entity();
  e->addComponent(&c);

  auto s = KeyboardEvents<aronnax::EvUserMovement>();
  s.onAddEntity(*e);

  e->on(EV_USER_MOVEMENT, [&](aronnax::EvUserMovement* ev) {

  });

  e->emit(aronnax::EV_KEY, &ev);
}

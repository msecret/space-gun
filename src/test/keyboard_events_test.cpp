
#include <map>
#include <string>

#include <gtest/gtest.h>

#include "../lib/entity.h"

#include "../c_keyboardable.h"
#include "../s_keyboard_events.h"

using namespace std;
using namespace spacegun;

TEST(Keyboardable, Constructor) {
  unsigned int expected = 1;
  map<string, unsigned int> keyMap;
  keyMap["testa"] = expected;

  Keyboardable c = Keyboardable(keyMap);

  auto actual = c.getAction("testa");

  EXPECT_EQ(expected, actual);
}

TEST(Keyboardable, getType) {
  Keyboardable c;

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_KEYBOARDABLE);
}

TEST(Keyboardable, getKeys) {
  string expectedA = "testa";
  string expectedB = "testb";
  map<string, unsigned int> keyMap;
  keyMap[expectedA] = 1;
  keyMap[expectedB] = 1;

  Keyboardable c = Keyboardable(keyMap);

  // TODO do maps in c++ guarantee an order?
  auto actualA = c.getKeys().at(0);
  auto actualB = c.getKeys().at(1);

  EXPECT_EQ(expectedA, actualA);
  EXPECT_EQ(expectedB, actualB);
}

TEST(Keyboardable, getAction) {
  unsigned int testA = 1;
  unsigned int testB = 2;
  map<string, unsigned int> expected;
  expected["testa"] = testA;
  expected["testb"] = testB;

  Keyboardable c = Keyboardable(expected);

  auto actualA = c.getAction("testa");
  auto actualB = c.getAction("testb");

  EXPECT_EQ(expected["testa"], actualA);
  EXPECT_EQ(expected["testb"], actualB);
}

TEST(KeyboardEvents, getType) {
  KeyboardEvents s;

  auto actual = s.getType();

  EXPECT_EQ(COMPONENT_TYPE_KEYBOARDABLE, actual);
}

TEST(KeyboardEvents, onAddEntity) {
  map<string, unsigned int> keyMap;
  string expectedKey = "A";
  unsigned int expectedEv = 101;

  KeyboardEvents s;
  Keyboardable c(keyMap);
  SDL_Event* expected = new SDL_Event;
  aronnax::Entity* e = new aronnax::Entity;

  e->addComponent(c);
}

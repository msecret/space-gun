
#include <gtest/gtest.h>

#include "../c_keyboardable.h"

#include <map>
#include <string>

using namespace std;
using namespace spacegun;

TEST(Keyboardable, Constructor) {
  unsigned int expected = 1;
  map<string, unsigned int> keyMap;
  keyMap["testa"] = expected;

  Keyboardable c = Keyboardable(keyMap);

  auto actual = c.getMovement("testa");

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

TEST(Keyboardable, getMovement) {
  unsigned int testA = 1;
  unsigned int testB = 2;
  map<string, unsigned int> expected;
  expected["testa"] = testA;
  expected["testb"] = testB;

  Keyboardable c = Keyboardable(expected);

  auto actualA = c.getMovement("testa");
  auto actualB = c.getMovement("testb");

  EXPECT_EQ(expected["testa"], actualA);
  EXPECT_EQ(expected["testb"], actualB);
}


#include <cstdint>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../lib/entity.h"
#include "../lib/renderer.h"
#include "../lib/units.h"

#include "../c_notification.h"
#include "../s_notify.h"

using std::string;
using std::vector;
using ::testing::_;
using aronnax::Color;
using aronnax::Vector2d;

using namespace spacegun;

namespace aronnax {
class MockRenderer: public IRenderer
{
  public:
    MOCK_METHOD0(render,
        void());
    MOCK_METHOD0(beforeRender,
        void());
    MOCK_METHOD0(afterRender,
        void());
    MOCK_METHOD2(drawCircle,
        void(const Vector2d& pos, const Vector2d& r));
    MOCK_METHOD4(drawRectangle,
        void(const Vector2d& pos, const Vector2d& box, SDL_Texture* texture, float angle));
    MOCK_METHOD1(drawPolygon,
        void(const Vector2d& pos));
    MOCK_METHOD3(drawText,
        void(const Vector2d& pos, string message, const Color& color));
    MOCK_METHOD1(createTexture,
        SDL_Texture*(SDL_Surface& s));
    MOCK_METHOD1(loadImg,
        SDL_Surface*(const string& filePath));
};
}

TEST(Notification, Constructor) {
  Vector2d expectedPos = { 20, 25 };
  string expectedMsg = "hello";

  Notification c(expectedPos, expectedMsg, Color(255, 255, 255, 255));

  auto actualMsg = c.getLine(0);
  auto actualCol = c.getColor();

  EXPECT_EQ(actualMsg, expectedMsg);
  EXPECT_EQ(actualCol, Color(255, 255, 255, 255));
}

TEST(Notification, setgetColor) {
  Color expected(200, 100, 200, 255);
  Notification c(Vector2d(0, 0), "", Color(255, 255, 255, 255));

  c.setColor(expected);
  auto actual = c.getColor();

  EXPECT_EQ(actual, expected);
}

TEST(Notification, addLine) {
  int expected = 1;
  Notification c(Vector2d(0, 0), "player1", Color(255, 255, 255, 255));

  auto actual = c.addLine("health: 100");

  EXPECT_EQ(actual, expected);
}

TEST(Notification, updateLine) {
  string expected = "something here";
  Notification c(Vector2d(0, 0), "player1", Color(255, 255, 255, 255));

  auto lineNum = c.addLine(" ");
  c.updateLine(lineNum, expected);

  auto actual = c.getLine(lineNum);


  EXPECT_EQ(actual, expected);
}

TEST(Notification, getAllLines) {
  string expected = "playermain";
  Vector2d initPos = { 20, 40 };
  Color expectedCol = { 100, 50, 250, 255 };
  int fontSize = 10;

  Notification c(initPos, expected, expectedCol);
  c.setColor(expectedCol);
  c.setFontSize(fontSize);

  string expected1 = "something";
  auto lineNum = c.addLine(expected1);

  auto actuals = c.getAllLines();
  auto actual0 = actuals[0];
  auto actual1 = actuals[1];

  EXPECT_EQ(actual0.msg, expected);
  EXPECT_EQ(actual0.col, expectedCol);
  EXPECT_EQ(actual0.pos, initPos);

  Vector2d expectedPos;
  expectedPos.x = initPos.x;
  expectedPos.y = initPos.y + (fontSize * 1.2);

  EXPECT_EQ(actual1.msg, expected1);
  EXPECT_EQ(actual1.col, expectedCol);
  EXPECT_EQ(actual1.pos, expectedPos);
}

TEST(Notification, getType) {
  Notification c(Vector2d(0, 0), "player1", Color(255, 255, 255, 255));
  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_NOTIFICATION);
}

TEST(Notify, render) {
  Vector2d expectedPos = { 30, 50 };
  string expectedMsg = "player 1";
  Color expectedCol = { 100, 50, 250, 255 };
  int fontSize = 15;
  auto e = new Entity();

  Notification c(expectedPos, expectedMsg, expectedCol);
  c.setFontSize(fontSize);

  e->addComponent(&c);
  Entities list;
  list.push_back(e);

  MockRenderer rr;
  Notify s(&rr);

  EXPECT_CALL(rr, drawText(
      _,
      expectedMsg,
      expectedCol)).Times(1);

  s.render(0, list);

  delete e;
}

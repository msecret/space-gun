
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../lib/entity.h"
#include "../lib/renderer.h"
#include "../lib/units.h"

#include "../c_moveable.h"
#include "../c_rectangular.h"
#include "../c_rendered.h"
#include "../c_painted.h"
#include "../s_rectangle_renderer.h"

using namespace std;
using ::testing::_;

using aronnax::Color;
using aronnax::IRenderer;
using aronnax::Vector2d;

using namespace spacegun;

class MockRenderer: public IRenderer
{
  public:
    MOCK_METHOD0(render, void());
    MOCK_METHOD0(beforeRender, void());
    MOCK_METHOD0(afterRender, void());
    MOCK_METHOD4(drawRectangle, void(const Vector2d& pos,
          const Vector2d& box, SDL_Texture* texture, float angle));
    MOCK_METHOD2(drawCircle, void(const Vector2d& pos,
          const Vector2d& r));
    MOCK_METHOD1(drawPolygon, void(const Vector2d& pos));
    MOCK_METHOD1(createTexture, SDL_Texture*(SDL_Surface& s));
};

TEST(Rectangular, getType) {
  Rectangular c;
  EXPECT_EQ(COMPONENT_TYPE_RECTANGULAR, c.getType());
}

TEST(Rectangular, Constructor) {
  float expectedW = 3;
  float expectedH = 5;
  auto c = Rectangular(expectedW, expectedH);

  auto actualW = c.getW();
  auto actualH = c.getH();

  EXPECT_EQ(expectedW, actualW);
  EXPECT_EQ(expectedH, actualH);
}

TEST(Rectangular, getsetW) {
  float expected = 3;
  Rectangular c;
  c.setW(expected);
  auto actual = c.getW();

  EXPECT_EQ(expected, actual);
}

TEST(Rectangular, getsetH) {
  float expected = 3;
  Rectangular c;
  c.setH(expected);
  auto actual = c.getH();

  EXPECT_EQ(expected, actual);
}

TEST(Rectangular, getShape) {
  Rectangular c(10, 10);

  auto shape = c.getShape();
  auto actual = shape->m_centroid;

  EXPECT_EQ(actual.x, 0);
  EXPECT_EQ(actual.y, 0);
}

TEST(RectangleRenderer, constructor) {
  auto testRR = RectangleRenderer();
}

TEST(RectangleRenderer, getType) {
  RectangleRenderer testRR;

  auto actual = testRR.getType();

  EXPECT_EQ(COMPONENT_TYPE_RECTANGULAR, actual);
}

TEST(RectangleRenderer, init) {
  MockRenderer mockRenderer;
  auto testC = Rectangular(5, 7);
  auto testR = Rendered();
  auto testP = Painted();

  aronnax::Entities entities;
  auto testEntity = new aronnax::Entity();
  testEntity->addComponent(&testC);
  testEntity->addComponent(&testR);
  entities.push_back(testEntity);

  auto testRR = RectangleRenderer(&mockRenderer);

  EXPECT_CALL(mockRenderer, createTexture(_)).Times(1);

  testRR.init(entities);

  delete testEntity;
}

TEST(RectangleRenderer, render) {
  uint32_t testDt = 12;
  Color expectedC = { 255, 100, 150, 123 };
  Vector2d expectedP = { 1, 3 };
  Vector2d expectedV = { 1, 3 };
  Vector2d expectedB = { 10, 20 };
  float expectedAngle = 135.3;
  MockRenderer mockRenderer;
  aronnax::Entities entities;
  auto testC = Rectangular(expectedB.x, expectedB.y);
  auto testM = Moveable(expectedP, expectedV, expectedAngle);
  auto testP = Painted(expectedC);
  auto testR = Rendered();
  auto testEntity = new aronnax::Entity();
  auto testRR = RectangleRenderer(&mockRenderer);

  testEntity->addComponent(&testC);
  testEntity->addComponent(&testM);
  testEntity->addComponent(&testP);
  testEntity->addComponent(&testR);
  entities.push_back(testEntity);

  EXPECT_CALL(mockRenderer, drawRectangle(
        expectedP,
        expectedB,
        _,
        expectedAngle)).Times(1);

  testRR.render(testDt, entities);

  delete testEntity;
}


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../lib/entity.h"
#include "../lib/renderer.h"
#include "../lib/units.h"

#include "../c_rectangular.h"
#include "../c_painted.h"
#include "../s_rectangle_renderer.h"

using namespace std;
using ::testing::_;

class MockRenderer: public aronnax::IRenderer
{
  public:
    MOCK_METHOD0(render, void());
    MOCK_METHOD0(beforeRender, void());
    MOCK_METHOD0(afterRender, void());
    MOCK_METHOD3(drawRectangle, void(const aronnax::Vector2d& pos,
          const aronnax::Vector2d& box, const aronnax::Color& c));
    MOCK_METHOD2(drawCircle, void(const aronnax::Vector2d& pos,
          const aronnax::Vector2d& r));
    MOCK_METHOD1(drawPolygon, void(const aronnax::Vector2d& pos));
};

TEST(RectangleComponent, getType) {
  spacegun::Rectangular c;
  EXPECT_EQ(spacegun::COMPONENT_TYPE_RECTANGULAR, c.getType());
}

TEST(RectangleComponent, Constructor) {
  double expectedW = 3;
  double expectedH = 5;
  auto c = spacegun::Rectangular(expectedW, expectedH);

  auto actualW = c.getW();
  auto actualH = c.getH();

  EXPECT_EQ(expectedW, actualW);
  EXPECT_EQ(expectedH, actualH);
}

TEST(RectangleComponent, getsetW) {
  double expected = 3;
  spacegun::Rectangular c;
  c.setW(expected);
  auto actual = c.getW();

  EXPECT_EQ(expected, actual);
}

TEST(RectangleComponent, getsetH) {
  double expected = 3;
  spacegun::Rectangular c;
  c.setH(expected);
  auto actual = c.getH();

  EXPECT_EQ(expected, actual);
}

TEST(RectangleSystem, constructor) {
  auto testRR = spacegun::RectangleRenderer();
}

TEST(RectangleSystem, getType) {
  spacegun::RectangleRenderer testRR; 

  auto actual = testRR.getType();

  EXPECT_EQ(spacegun::COMPONENT_TYPE_RECTANGULAR, actual);
}

TEST(RectangleSystem, render) {
  uint32_t testDt = 12;
  aronnax::Color expectedC = { 255, 100, 150, 123 };
  aronnax::Vector2d expectedP = { 1, 3 };
  aronnax::Vector2d expectedB = { 5, 7 };
  MockRenderer mockRenderer;
  aronnax::Entities entities;
  auto testC = spacegun::Rectangular(5, 7);
  auto testP = spacegun::Painted(expectedC);
  auto testEntity = new aronnax::Entity();
  auto testRR = spacegun::RectangleRenderer(&mockRenderer);

  testEntity->setPos(expectedP);
  testEntity->addComponent(&testC);
  testEntity->addComponent(&testP);
  entities.push_back(testEntity);

  EXPECT_CALL(mockRenderer, drawRectangle(_, _, expectedC)).Times(1);

  testRR.render(testDt, entities);
}


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../lib/entity.h"
#include "../lib/renderer.h"
#include "../lib/sdl_renderer.h"
#include "../lib/units.h"

#include "../c_moveable.h"
#include "../c_rendered.h"
#include "../c_rectangular.h"
#include "../c_shaped.h"
#include "../c_painted.h"
#include "../s_sdl_paint_renderer.h"

using namespace std;
using namespace spacegun;

using aronnax::IRenderer;
using aronnax::Color;
using aronnax::Vector2d;
using aronnax::Vector2d;
using ::testing::_;

class MockRenderer: public SDLRenderer
{
  public:
    MOCK_METHOD0(Die, void());
    virtual ~MockRenderer() { Die(); }

    MOCK_METHOD0(render, void());
    MOCK_METHOD0(beforeRender, void());
    MOCK_METHOD0(afterRender, void());
    using SDLRenderer::drawCircle;
    MOCK_METHOD4(drawRectangle, void(const Vector2d& pos,
          const Vector2d& box, SDL_Texture* texture, float angle));
    using SDLRenderer::drawPolygon;
    using SDLRenderer::drawText;
    MOCK_METHOD1(createTexture, SDL_Texture*(SDL_Surface& s));
    MOCK_METHOD1(loadImg, SDL_Surface*(const string& filePath));
};

TEST(Painted, DefaultConstructor) {
  aronnax::Color expected;
  Painted c = Painted();
  auto actual = c.getColor();

  EXPECT_EQ(expected, actual);
}

TEST(Painted, ColorConstructor) {
  aronnax::Color expected = { 155, 155, 255, 155 };
  Painted c = Painted(expected);

  auto  actual = c.getColor();

  EXPECT_EQ(expected, actual);
}

TEST(Painted, RGBAConstructor) {
  aronnax::Color e = { 234, 155, 0, 255 };
  Painted c = Painted(e.r, e.g, e.b, e.a);

  auto  actual = c.getColor();

  EXPECT_EQ(e, actual);
}

TEST(Painted, getType) {
  Painted c = Painted();

  auto actual = c.getType();

  EXPECT_EQ(COMPONENT_TYPE_PAINTED, actual);
}

TEST(Painted, getsetColor) {
  aronnax::Color expected = { 155, 155, 255, 155 };
  Painted c = Painted();

  c.setColor(expected);
  auto actual = c.getColor();

  EXPECT_EQ(expected, actual);
}

TEST(SDLPaintRenderer, constructor) {
  auto testRR = SDLPaintRenderer();
}

TEST(SDLPaintRenderer, getType) {
  SDLPaintRenderer testRR;

  auto actual = testRR.getType();

  EXPECT_EQ(COMPONENT_TYPE_PAINTED, actual);
}

TEST(SDLPaintRenderer, initPainted) {
  MockRenderer mockRenderer;
  Color color = { 255, 100, 150, 255 };
  auto testC = Rectangular(5, 7);
  auto testS = Shaped(testC);
  auto testR = Rendered();
  auto testP = Painted(color);

  aronnax::Entities entities;
  auto testEntity = new aronnax::Entity();
  testEntity->addComponent(&testC);
  testEntity->addComponent(&testR);
  testEntity->addComponent(&testP);
  testEntity->addComponent(&testS);
  entities.push_back(testEntity);

  auto testRR = SDLPaintRenderer(&mockRenderer);

  testRR.init(entities);

  delete testEntity;
}

TEST(SDLPaintRenderer, render) {
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
  auto testRR = SDLPaintRenderer(&mockRenderer);

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

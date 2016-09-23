
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
#include "../s_paint_renderer.h"

using namespace std;
using namespace spacegun;

using aronnax::IRenderer;
using aronnax::Color;
using aronnax::Vector2d;
using aronnax::Vector2d;
using ::testing::_;

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

TEST(PaintRenderer, constructor) {
  auto testRR = PaintRenderer<SDLRenderer>();
}

TEST(PaintRenderer, getType) {
  PaintRenderer<SDLRenderer> testRR;

  auto actual = testRR.getType();

  EXPECT_EQ(COMPONENT_TYPE_PAINTED, actual);
}

TEST(PaintRenderer, init) {
  auto color = Color(10, 100, 200, 255);
  auto entity = new Entity();

  auto rectangular = Rectangular(10, 10);
  auto rendered = Rendered();
  auto shaped = Shaped(rectangular);
  auto painted = Painted(color);

  Entities entities;
  entity->addComponent(&rectangular);
  entity->addComponent(&rendered);
  entity->addComponent(&shaped);
  entity->addComponent(&painted);
  entities.push_back(entity);

  MockRenderer mockRenderer;
  auto paintRenderer = PaintRenderer<MockRenderer>(&mockRenderer);

  EXPECT_CALL(mockRenderer, createTexture(_)).Times(1);

  paintRenderer.init(entities);

  delete entity;
}

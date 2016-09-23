
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


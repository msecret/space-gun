
#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../lib/entity.h"
#include "../lib/renderer.h"
#include "../lib/units.h"

#include "../c_moveable.h"
#include "../c_rendered.h"
#include "../c_rectangular.h"
#include "../c_shaped.h"
#include "../c_sprited.h"
#include "../s_sprite_renderer.h"

using std::string;
using ::testing::_;
using aronnax::Entity;
using aronnax::Entities;
using aronnax::IRenderer;
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

template class SpriteRenderer<MockRenderer>;

TEST(Sprited, DefaultConstructor) {
  string expected = "/path/to/img.gif";
  Sprited c = Sprited(expected);
  auto actual = c.getFilePath();

  EXPECT_EQ(expected, actual);
}

TEST(Sprited, getType) {
  Sprited c = Sprited("/path");

  auto actual = c.getType();

  EXPECT_EQ(COMPONENT_TYPE_SPRITED, actual);
}

TEST(Sprited, getFilePath) {
  string expected = "/path/to/img.gif";
  Sprited c = Sprited(expected);

  auto actual = c.getFilePath();

  EXPECT_EQ(expected, actual);
}

TEST(SpriteRenderer, init) {
  string imgPath = "../path/to/img";
  auto entity = new Entity();

  auto rectangular = Rectangular(10, 10);
  auto rendered = Rendered();
  auto shaped = Shaped(rectangular);
  auto sprited = Sprited(imgPath);

  Entities entities;
  entity->addComponent(&rectangular);
  entity->addComponent(&rendered);
  entity->addComponent(&shaped);
  entity->addComponent(&sprited);
  entities.push_back(entity);

  MockRenderer mockRenderer;
  auto spriteRenderer = SpriteRenderer<MockRenderer>(&mockRenderer);

  EXPECT_CALL(mockRenderer, loadImg(imgPath)).Times(1);
  EXPECT_CALL(mockRenderer, createTexture(_)).Times(1);

  spriteRenderer.init(entities);

  delete entity;
}

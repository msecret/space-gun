
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../lib/component.h"
#include "../lib/entity.h"
#include "../lib/units.h"

#include "../c_armed.h"
#include "../s_arm.h"

using ::testing::NiceMock;
using ::testing::Return;

using aronnax::EV_WEAPON_FIRED;
using aronnax::Component;
using aronnax::Entity;
using aronnax::EvWeaponFired;

using spacegun::COMPONENT_TYPE_ARMED;
using spacegun::Armed;
using spacegun::Arm;

class MockArmed : public Component
{
  public:
    MockArmed(Entity* entity) {};
    MOCK_METHOD0(getType, const string());
    MOCK_METHOD0(getWeapon, Entity*());
    MOCK_METHOD0(activate, void());

};

class ArmTest : public testing::Test {
  protected:
    virtual void SetUp() {
      entity_ = new Entity();
    }

    virtual void TearDown()
    {
      delete entity_;
    }

    Entity* entity_;
};

TEST_F(ArmTest, getType) {
  Armed c(entity_);

  auto actual = c.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_ARMED);
}

TEST_F(ArmTest, getWeaponEntity) {
  Armed c(entity_);

  auto actual = c.getWeapon();

  EXPECT_EQ(actual, entity_);
}

TEST(Arm, getType) {
  Arm s;

  auto actual = s.getType();

  EXPECT_EQ(actual, COMPONENT_TYPE_ARMED);
}

TEST_F(ArmTest, onAddEntity) {
  NiceMock<MockArmed> mockArmed(entity_);

  ON_CALL(mockArmed, getType())
    .WillByDefault(Return(COMPONENT_TYPE_ARMED));

  auto testEntity = new Entity();

  testEntity->addComponent(&mockArmed);

  const unsigned int expectedClass = 2;
  EvWeaponFired ev(expectedClass);

  Arm arm;
  arm.onAddEntity(*testEntity);

  testEntity->emit(EV_WEAPON_FIRED, &ev);

  delete testEntity;
}

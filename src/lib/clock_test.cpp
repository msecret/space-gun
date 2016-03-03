
#include <memory>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "clock.h"

using ::testing::_;
using ::testing::NiceMock;

class MockRunner {
  public:
    MOCK_METHOD1(update, void(const uint32_t dt));
};

class ClockTest: public testing::Test {
  protected:
    virtual void SetUp() {
      clock_ = new aronnax::Clock();
    }

    virtual void TearDown() {
      clock_->stop();
      delete clock_;
    }

    aronnax::Clock* clock_;
};

TEST_F(ClockTest, start) {
  EXPECT_FALSE(clock_->isStarted());
  //clock_->start();
  //EXPECT_TRUE(clock_->isStarted());
  //clock_->stop();
}

TEST_F(ClockTest, isStarted) {
  EXPECT_FALSE(clock_->isStarted());
}

TEST_F(ClockTest, tickConstantly) {
  using namespace std::placeholders;
  const uint32_t testDt = 1;
  NiceMock<MockRunner> runnerA;
  NiceMock<MockRunner> runnerB;
  std::function<void(const uint32_t)> f_updateA = std::bind(
      &MockRunner::update, &runnerA, _1);
  std::function<void(const uint32_t)> f_updateB = std::bind(
      &MockRunner::update, &runnerB, _1);

  clock_->onConstantly(f_updateA);
  clock_->onConstantly(f_updateB);

  EXPECT_CALL(runnerA, update(testDt)).Times(1);
  EXPECT_CALL(runnerB, update(testDt)).Times(1);

  clock_->tickConstantly(testDt);
}

TEST_F(ClockTest, tickEveryFrame) {
  using namespace std::placeholders;
  const uint32_t testDt = 1;
  NiceMock<MockRunner> runnerA;
  NiceMock<MockRunner> runnerB;
  std::function<void(const uint32_t)> f_renderA = std::bind(
      &MockRunner::update, &runnerA, _1);
  std::function<void(const uint32_t)> f_renderB = std::bind(
      &MockRunner::update, &runnerB, _1);

  clock_->onEveryFrame(f_renderA);
  clock_->onEveryFrame(f_renderB);

  EXPECT_CALL(runnerA, update(testDt)).Times(1);
  EXPECT_CALL(runnerB, update(testDt)).Times(1);

  clock_->tickEveryFrame(testDt);
}

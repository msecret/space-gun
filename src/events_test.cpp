
#include "gtest/gtest.h"

#include "c_evented.h"
#include "s_sdl_events.h"

TEST(Events, getType) {
  spacegun::Events testEvents;
  auto actual = testEvents.getType();

  EXPECT_EQ(spacegun::COMPONENT_TYPE_EVENTED, actual);
}

// Copyright 2021 GHA Test Team

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include "TimedDoor.h"

TEST(TimedDoorTest, testDoorTimerWorking) {
  TimedDoor tDoor(5);
  ASSERT_ANY_THROW(tDoor.unlock());
}
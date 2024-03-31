// Copyright 2021 GHA Test Team

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include "TimedDoor.h"

class MockTimerClient : public TimerClient {
public:
  MOCK_METHOD(void, Timeout, ());
};

class TimedDoorTest : public ::testing::Test {
protected:
  void SetUp() override {
    door = new TimedDoor(100);
  }

  void TearDown() override {
    delete door;
  }

  TimedDoor* door;
};

TEST(TimerTest, testCanGetTimeOutValue) {
  TimedDoor door(5);
  EXPECT_EQ(door.getTimeOut(), 5);
}

TEST(TimerTest, testTimerClientRegistered) {
  Timer timer;
  MockTimerClient client;
  EXPECT_CALL(client, Timeout()).Times(1);
  timer.tregister(100, &client);
}
TEST_F(TimedDoorTest, testLockWorks) {
  door->unlock();
  door->lock();
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, testOpenWorks) {
  door->unlock();
  EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, testCheckIsClosed) {
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, testTimeOutDoor) {
  door->unlock();
  door->lock();
  EXPECT_THROW(door->throwState(), std::runtime_error);
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, testeOutDoorOpened) {
  door->unlock();
  EXPECT_THROW(door->throwState());
  EXPECT_TRUE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, testTimeOutDoorClosed) {
  EXPECT_NO_THROW(door->throwState(), std::runtime_error);
  EXPECT_FALSE(door->isDoorOpened());
}

TEST_F(TimedDoorTest, testTimeOutDoorOpened) {
  door->unlock();
  EXPECT_THROW(door->throwState());
  EXPECT_TRUE(door->isDoorOpened());
}
// Copyright 2021 GHA Test Team

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include "TimedDoor.h"

class TimerClientMock : public TimerClient {
public:
    MOCK_METHOD(void, Timeout, (), (override));
};

class TimedDoorMock : public Door {
public:
    MOCK_METHOD(bool, isDoorOpened, (), (override));
    MOCK_METHOD(void, unlock, (), (override));
    MOCK_METHOD(void, lock, (), (override));
};

class DoorTimerAdapterTest : public ::testing::Test {
protected:
    void SetUp() override {

        timerClientMock = std::make_unique<StrictMock<TimerClientMock>>();
        timedDoorMock = std::make_unique<StrictMock<TimedDoorMock>>();

        doorTimerAdapter = std::make_unique<DoorTimerAdapter>(*timedDoorMock);
    }

    void TearDown() override {
        doorTimerAdapter.reset();
        timerClientMock.reset();
        timedDoorMock.reset();
    }

    std::unique_ptr<TimerClientMock> timerClientMock;
    std::unique_ptr<TimedDoorMock> timedDoorMock;
    std::unique_ptr<DoorTimerAdapter> doorTimerAdapter;
};

TEST_F(DoorTimerAdapterTest, Timeout_CalledWhenTimeoutOccurs) {
    EXPECT_CALL(*timerClientMock, Timeout()).Times(1);

    doorTimerAdapter->Timeout();
}

TEST_F(DoorTimerAdapterTest, Timeout_ThrowsExceptionWhenDoorIsOpened) {
    ON_CALL(*timedDoorMock, isDoorOpened()).WillByDefault(Return(true));
    EXPECT_CALL(*timedDoorMock, throwState()).Times(1);

    doorTimerAdapter->Timeout();
}
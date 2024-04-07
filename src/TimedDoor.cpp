// Copyright 2024 Vinokurov Ivan

#include "TimedDoor.h"
#include <stdexcept>
#include <iostream>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& door) : door(door) {}

void DoorTimerAdapter::Timeout() {
  door.throwState();
}

TimedDoor::TimedDoor(int timeout) {
  iTimeout = timeout;
  isOpened = false;
  adapter = new DoorTimerAdapter(*this);
}

bool TimedDoor::isDoorOpened() {
  return isOpened;
}

void TimedDoor::unlock() {
  isOpened = true;
  adapter->Timeout();
}

void TimedDoor::lock() {
  isOpened = false;
}

int TimedDoor::getTimeOut() const {
  if (isOpened) {
    throw std::runtime_error("Door Timeout");
  }
  return 1;
}

void TimedDoor::throwState() {
  getTimeOut();
}

void Timer::sleep(int time) {
  for (int i = time; i > 0; i--) {}
}

void Timer::tregister(int time, TimerClient* client) {
  sleep(time);
  client->Timeout();
}

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
}

bool TimedDoor::isDoorOpened() {
  return isOpened;
}

void TimedDoor::unlock() {
  isOpened = true;
  Timer timer;
  timer.tregister(getTimeOut(), adapter);
}

void TimedDoor::lock() {
  isOpened = false;
}

int TimedDoor::getTimeOut() const {
  return iTimeout;
}

void TimedDoor::throwState() {
  if (isOpened == true) {
       throw std::runtime_error("Door timeout");
  }
}

void Timer::sleep(int time) {
  for (int i = time; i > 0; i--) {}
}

void Timer::tregister(int time, TimerClient* client) {
  sleep(time);
  client->Timeout();
}

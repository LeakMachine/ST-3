// Copyright 2024 Vinokurov Ivan

#include "TimedDoor.h"
#include <stdexcept>
#include <iostream>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& _door) : door(_door) {}

void DoorTimerAdapter::Timeout() {
  door.throwState();
}

TimedDoor::TimedDoor(int _timeout) {
  iTimeout = _timeout;
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

int TimedDoor::getTimeOut() {
  return iTimeout;
}

void TimedDoor::throwState() {
  if (isOpened == true) {
       throw std::runtime_error("Door timeout");
  }
}

void Timer::sleep(int _time) {
  for (int i = _time; i > 0; i--);
}

void Timer::tregister(int _time, TimerClient* _client) {
  sleep(_time);
  _client->Timeout();
}

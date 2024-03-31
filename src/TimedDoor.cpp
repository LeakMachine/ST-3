// Copyright 2024 Vinokurov Ivan

#include "TimedDoor.h"
#include <stdexcept>
#include <iostream>
#include <chrono>
#include <thread>

DoorTimerAdapter::DoorTimerAdapter(TimedDoor& _door) : door(_door) {}

void DoorTimerAdapter::Timeout() {
	if (door.isDoorOpened() == true) {
		door.throwState();
	}
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
	throw std::runtime_error("Door timeout reached without door being closed!");
}

void Timer::sleep(int _time) {
	std::this_thread::sleep_for(std::chrono::seconds(_time));
}

void Timer::tregister(int _time, TimerClient* _client) {
	sleep(_time);
	_client->Timeout();
}

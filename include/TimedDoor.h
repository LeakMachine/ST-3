// Copyright 2021 GHA Test Team

#ifndef INCLUDE_TIMEDDOOR_H_
#define INCLUDE_TIMEDDOOR_H_

class DoorTimerAdapter;
class Timer;
class Door;
class TimedDoor;

class TimerClient {
 public:
  virtual void Timeout() = 0;
};

class Door {
 public:
  virtual void lock() = 0;
  virtual void unlock() = 0;
  virtual bool isDoorOpened() = 0;
};

class DoorTimerAdapter : public TimerClient {
 private:
  TimedDoor& door;
 public:
  explicit DoorTimerAdapter(const TimedDoor& _door);
  void Timeout();
};

class TimedDoor : public Door {
 private:
  DoorTimerAdapter * adapter;
  int iTimeout;
  bool isOpened;
 public:
  explicit TimedDoor(int _timeout);
  bool isDoorOpened();
  void unlock();
  void lock();
  int getTimeOut();
  void throwState();
};

class Timer {
  TimerClient *client;
  void sleep(int _time);
 public:
  void tregister(int _time, TimerClient* _timer);
};

#endif  // INCLUDE_TIMEDDOOR_H_

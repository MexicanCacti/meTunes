#pragma once
#include <ctime>

class Timer {
  private:
    clock_t pstartTime;
    clock_t pendTime;
    double totalPaused;
    clock_t startTime;
    clock_t endTime;
  public:
    Timer();
    void Start();
    void Pause();
    void Resume();
    int Convert();
    
};

Timer::Timer() {
  totalPaused = 0.0;
}

void Timer::Start() {
  startTime = clock();
}

void Timer::Pause() {
  pstartTime = clock();
}

void Timer::Resume() {
  pendTime = clock();
  totalPaused += (pendTime - pstartTime);
}

int Timer::Convert() {
  int totalTime;
  endTime = clock();
  totalTime = ((endTime - startTime - totalPaused) / CLOCKS_PER_SEC) * 1000; //subtract the totalPaused / clocks_per_sec to get seconds. Then multiply by 1000
  return totalTime;
}
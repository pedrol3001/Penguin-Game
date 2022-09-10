#include "Timer.h"

Timer::Timer(float time) :
  time(time) {
}

Timer::Timer() : Timer(0) {}

void Timer::Update(float dt) {
	time += dt;
}

void Timer::Restart() {
	time = 0;
}

float Timer::Get() {
	return time;
}

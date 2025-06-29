#include "Time.h"

Time::Time(Uint64 expectedFPS) :
	frameGap(Uint64(1000) / expectedFPS) {};

Uint64 Time::current_time() {
	return SDL_GetTicks();
}

Uint64 Time::frame_delta() {
	Uint64 totalTime = current_time();
	Uint64 deltaTime = totalTime - accumulator;
	return deltaTime;
}

void Time::sleep_delta() {
	Uint64 deltaTime = frame_delta();
	bool desynced = false;

	Uint32 sleepTime;
	if (deltaTime > frameGap) {
		bool desynced = true;
		sleepTime = 0;
	}
	else {
		sleepTime = static_cast<Uint32>(frameGap - deltaTime);
	}

	SDL_Delay(sleepTime);

	if (!desynced) {
		accumulator += frameGap;
	}
	else {
		accumulator = deltaTime;
	}
}
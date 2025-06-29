#pragma once
#ifndef TIME
#define TIME

#include <SDL3/SDL.h>
#include <iostream>

class Time {
public:
	Time(Uint64 expectedGap);

	Uint64 current_time();
	
	Uint64 frame_delta();

	void sleep_delta();
	
private:
	Uint64 accumulator = 0;
	const Uint64 frameGap;
};

#endif
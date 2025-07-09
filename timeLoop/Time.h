#pragma once
#ifndef TIME
#define TIME

#include <SDL3/SDL.h>
#include <iostream>

class Time {
public:
    // === Constructor ===
    Time(Uint64 expectedGap);

    // === Public Methods ===
    Uint64 current_time();
    Uint64 frame_delta();
    void sleep_delta();
    Uint64 current_frame();

private:
    // === Timing State ===
    Uint64 accumulator = 0;
    Uint64 frameCount = 0;
    const Uint64 frameGap;
};

#endif

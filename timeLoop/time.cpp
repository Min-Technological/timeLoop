#include "Time.h"

// === Constructor: initialize expected frame gap based on target FPS ===
Time::Time(Uint64 expectedFPS) :
    frameGap(Uint64(1000) / expectedFPS) {
}

// === Get current time in milliseconds since SDL init ===
Uint64 Time::current_time() {
    return SDL_GetTicks();
}

// === Calculate time elapsed since last frame ===
Uint64 Time::frame_delta() {
    Uint64 totalTime = current_time();
    Uint64 deltaTime = totalTime - accumulator;
    return deltaTime;
}

// === Sleep if needed to cap FPS, and update accumulator and frame count ===
void Time::sleep_delta() {
    Uint64 deltaTime = frame_delta();
    bool desynced = false;
    Uint32 sleepTime;

    if (deltaTime > frameGap) {
        desynced = true;
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
        accumulator = current_time();
    }

    frameCount += 1;
}

// === Get current frame number ===
Uint64 Time::current_frame() const {
    return frameCount;
}

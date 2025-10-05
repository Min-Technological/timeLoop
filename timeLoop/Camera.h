#pragma once
#ifndef CAMERA
#define CAMERA

#include "Character.h"
#include "Input.h"
#include "Time.h"

class Camera {
public:
    // === Constructor ===
    Camera(Character& character, Time& mainTime, int& screenW, int& screenH, float& screenScale);

    // === Public Methods ===
    void affect(Input input);
    void update();

    // === Public Fields ===
    int& w;  // Viewport Width
    int& h;  // Viewport Height
    float xOffset = 0;
    float yOffset = 0;

private:
    // === References ===
    Character& user;
    Time& time;
    float& scale;

    // === Internal State ===
    float x = 0;
    float y = 0;

    float leftBounds = 480;
    float rightBounds = 1440;
    float boundsCount = 4;

    float leftEdge = 0;
    float rightEdge = 128.0f * 40.0f;

    bool shaking = false;
    Uint64 shakeStart = 0;

    // === Private Helpers ===
    float lerp(float current, float target, float blend);
    float target(float velocity);
    void shake_effect();
};

#endif

#pragma once
#ifndef CAMERA
#define CAMERA

#include "Character.h"
#include "Input.h"
#include "Time.h"

class Camera {
public:
    // === Constructor ===
    Camera(Character& character, Time& mainTime, int& screenW, int& screenH, float& screenScale, float& playerDepthValue);

    // === Public Methods ===
    void affect(Input input);
    void update();

    // === Loop Management ===
    void save_loop_data(PassiveData* passiveData);
    void load_loop_data(PassiveData* passiveData);

    /// x = 0, y = 1, w = 2, h = 3
    float get_coordinate(int coord);
    float get_depth();

    void move_position(float x, float y, float z);
    void zoom(float z);

private:
    // === References ===
    Character& user;
    Time& time;
    float& scale;
    float cameraDepth = 0;
    float& playerDepth;

    // === Internal State ===
    float xOffset = 0;
    float yOffset = 0;
    int& w;  // Viewport Width
    int& h;  // Viewport Height

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

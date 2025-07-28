#include "Camera.h"

// === Constructor ===
Camera::Camera(Character& character, Time& mainTime, int& screenW, int& screenH, float& screenScale) :
    user(character), w(screenW), h(screenH), scale(screenScale), time(mainTime) {
}

// === Apply Camera Effects ===
void Camera::affect(Input input) {
}

// === Update Camera Position & Effects ===
void Camera::update() {
    leftBounds = static_cast<float>(w) / boundsCount;
    rightBounds = leftBounds * (boundsCount - 1);

    float userCentre = user.hitbox.xa + (user.w / 2.0f);
    float screenPlayerPos = (userCentre - xOffset) * scale;

    if (screenPlayerPos < leftBounds) {
        xOffset = (userCentre - leftBounds / scale);
    }
    else if (screenPlayerPos > rightBounds) {
        xOffset = (userCentre - rightBounds / scale);
    }

    // Clamp camera within edges
    float rightClamp = rightEdge - (static_cast<float>(w) / scale);

    if (xOffset < leftEdge) {
        xOffset = leftEdge;
    }
    else if (xOffset > rightClamp) {
        xOffset = rightClamp;
    }

    // Apply shake effect if active
    if (!shaking) return;

    Uint64 deltaTime = time.current_time() - shakeStart;
    if (!(deltaTime >= 1000)) {
        bool shakeDirection = deltaTime % 2;
        xOffset += shakeDirection ? 5 : -5;
    }
    else {
        shaking = false;
    }
}

// === Start Shake Effect ===
void Camera::shake_effect() {
    if (!shaking) {
        shaking = true;
        shakeStart = time.current_time();
    }
}

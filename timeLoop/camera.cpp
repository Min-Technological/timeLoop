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

    // Right Edge Clamp
    float rightClamp = rightEdge - (static_cast<float>(w) / scale);

    float userCentre = user.hitbox.xa + (user.w / 2.0f);
    float screenPlayerPos = (userCentre - xOffset) * scale;

    float xVelocity = user.get_velocity()[0];

    float camTarget = target(xVelocity);
    if (xVelocity < 0) {
        if (camTarget < leftEdge) {
            camTarget = leftEdge;
        }
    }
    else if (xVelocity > 0) {
        if (camTarget > rightClamp) {
            camTarget = rightClamp;
        }
    }

    if (xVelocity <= 5 && xVelocity >= -5) {
        xOffset = lerp(xOffset, userCentre - camTarget, 0.02f);
    }
    else {
        xOffset = lerp(xOffset, userCentre - camTarget, 0.04f);
    }

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

// === LERP (Smooth transition) ===
float Camera::lerp(float current, float target, float blend) {
    return current + (target - current) * blend;
}
float Camera::target(float velocity) {

    float tempVelocity = velocity;
    float factor = -1;
    bool neg = false;

    // if negative, set state and make it positive
    if (velocity < 0) {
        neg = true;
        tempVelocity = -velocity;
    }

    // check boundary
    if (tempVelocity > 10) {
        factor = 1;
    }
    else {
        factor = tempVelocity / 10;
    }

    //window width
    float width = static_cast<float>(w) / scale;

    // Exponential Factor
    float eFactor = factor * factor * factor;

    if (neg) {
        return  (width / 2) * eFactor + (width / 2);
    }
    else {
        return (width / 2) * (1 - eFactor);
    }

}

// === Start Shake Effect ===
void Camera::shake_effect() {
    if (!shaking) {
        shaking = true;
        shakeStart = time.current_time();
    }
}

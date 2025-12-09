#include "Camera.h"

// === Constructor ===
Camera::Camera(Character& character, Time& mainTime, int& screenW, int& screenH, float& screenScale, float& playerDepthValue) :
    user(character), w(screenW), h(screenH), scale(screenScale), time(mainTime), playerDepth(playerDepthValue) {
}

// === Apply Camera Effects ===
void Camera::affect(Input input) {
}
 
// === Update Camera Position & Effects ===
void Camera::update() {

    std::array<float, 4> userCurrentPos = user.hitbox.get_current_pos();

    leftBounds = static_cast<float>(w) / boundsCount;
    rightBounds = leftBounds * (boundsCount - 1);

    // Right Edge Clamp
    float rightClamp = (rightEdge - ((static_cast<float>(w) / scale) * playerDepth));

    float userCentre = userCurrentPos[0] + (user.w / 2.0f);

    float xVelocity = user.get_velocity()[0];

    float camTargetX = target(xVelocity);
    float camTargetY = userCurrentPos[1] - 600;

    if (camTargetX < leftEdge) {
        camTargetX = leftEdge;
    }
    else if (camTargetX > rightClamp) {
        camTargetX = rightClamp;
    }

    if (xVelocity <= 5 && xVelocity >= -5) {
        rate = 0.01f;
    }
    else {
        rate = 0.04f;
    }



    xOffset = lerp(xOffset, (userCentre - camTargetX), rate);
    yOffset = lerp(yOffset, camTargetY, rate);



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

// === Loop Management ===
void Camera::save_loop_data(PassiveData* passiveData) {
    passiveData->set_camera_position(xOffset, yOffset);
}
void Camera::load_loop_data(PassiveData* passiveData) {
    std::array<float, 2> cameraPos = passiveData->get_camera_position();

    xOffset = cameraPos[0];
    yOffset = cameraPos[1];
}

float Camera::get_coordinate(int coord) {
    switch (coord) {
    case 0:
        return static_cast<float>(xOffset);
    case 1:
        return static_cast<float>(yOffset);
    case 2:
        return static_cast<float>(w);
    case 3:
        return static_cast<float>(h);
    default:
        return 0.0f;
    }
}
float Camera::get_depth() {
    return cameraDepth;
}
void Camera::move_position(float x, float y, float z) {
    xOffset = lerp(xOffset, x, 0.1f);
    yOffset = lerp(yOffset, y, 0.1f);
    cameraDepth = lerp(cameraDepth, z, 0.1f);
}
void Camera::zoom(float z) {
    cameraDepth = lerp(cameraDepth, z, rate);
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
    float width = (static_cast<float>(w) / scale);

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

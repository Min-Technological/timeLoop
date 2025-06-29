#include "Camera.h"

Camera::Camera(Character &character, Time &mainTime, int &screenW, int &screenH, float &screenScale) :
	user(character), w(screenW), h(screenH), scale(screenScale), time(mainTime) {
}

void Camera::affect() {

	const bool* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_R]) {
		shake_effect();
	}


}

void Camera::update() {

	leftBounds = float(w) / boundsCount;
	rightBounds = leftBounds * (boundsCount - 1);

	float userCentre = user.hitbox.xa + (user.w / 2.0f);
	float screenPlayerPos = (userCentre - xOffset) * scale;

	if (screenPlayerPos < leftBounds) {

		xOffset = (userCentre - leftBounds / scale);

	}
	else if (screenPlayerPos > rightBounds) {

		xOffset = (userCentre - rightBounds / scale);

	}

	// CLAMPING
	float rightClamp = rightEdge - (float(w) / scale);

	if (xOffset < leftEdge) {
		xOffset = leftEdge;
	}
	else if (xOffset > (rightClamp)) {
		xOffset = rightClamp;
	}

	// EFFECTS

	if (shaking) {
		int deltaTime = time.current_time() - shakeStart;
		if (!(deltaTime >= 1000)) {
			bool shakeDirection = deltaTime % 2;
			if (shakeDirection) {
				xOffset -= 5;
			}
			else {
				xOffset += 5;
			}
		}
		else {
			shaking = false;
		}
	}
}

void Camera::shake_effect() {
	if (!shaking) {
		shaking = true;
		shakeStart = time.current_time();
	}
}

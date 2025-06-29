#pragma once
#ifndef CAMERA
#define CAMERA

#include "Character.h"
#include "Time.h"

class Camera {
public:
	Camera(Character &character, Time &mainTime, int &screenW, int&screenH, float &screenScale);

	void affect();

	void update();

	int &w; // Viewport Width
	int &h; // Viewport Height

	float xOffset = 0;
	float yOffset = 0;

private:
	Character &user;
	Time &time;

	float x = 0;
	float y = 0;

	float leftBounds;
	float rightBounds;
	float boundsCount = 4;

	float& scale;

	float leftEdge = 0;
	float rightEdge = 4000;

	bool shaking = false;
	Uint64 shakeStart = 0;
	void shake_effect();


};


#endif
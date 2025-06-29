#pragma once
#ifndef HITBOX
#define HITBOX

#include <iostream>

class Hitbox {
public:
	Hitbox();
	Hitbox(float x, float y, float width, float height);

	void check_collision(Hitbox other) const;

	float xa; // Left Side
	float xb; // Right Side
	float ya; // Top Side
	float yb; // Bottom Side

private:
};


#endif
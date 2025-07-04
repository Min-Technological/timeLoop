#pragma once
#ifndef HITBOX
#define HITBOX

#include <iostream>
#include <SDL3/SDL.h>

class Hitbox {
public:
	Hitbox();
	Hitbox(float x, float y, float width, float height);

	void update_hitbox(float x, float y, float width, float height);

	void enable_collisions(bool status);
	bool allows_collisions();

	bool check_collision(Hitbox other) const;

	void render_hitbox(SDL_Renderer* r, float xOffset, float scale, int green);

	float xa; // Left Side
	float xb; // Right Side
	float ya; // Top Side
	float yb; // Bottom Side

private:

	bool allowsCollisions = true;
};


#endif
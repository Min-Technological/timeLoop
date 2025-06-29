#pragma once
#ifndef CHARACTER
#define CHARACTER

#include <SDL3/SDL.h>
#include "Window.h"
#include "Hitbox.h"

class Character {
public:
	Character(float x, float y, float width, float height, AppWindow window);

	void handle_event(bool fullscreen);

	void move();

	void update(float viewScale, float xOffset);

	void render();

	Hitbox hitbox;

	float renderX, renderY;

	float w; // Width
	float h; // Height
private:
	void moveUp(int px);
	void moveLeft(int px);
	void moveDown(int px);
	void moveRight(int px);

	float newX; // predicted x
	float newY; // predicted y

	float renderW, renderH;
	float fullscreenScale;
	float scale;

	SDL_FRect t; // texture
	SDL_Renderer* r; // renderer
	AppWindow appWindow;

	// On the ground, vs falling / jumping
	bool grounded = true; 
	bool sprinting = false;

	void set_texture(float xOffset);
};

#endif
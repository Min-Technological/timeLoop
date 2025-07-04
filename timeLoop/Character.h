#pragma once
#ifndef CHARACTER
#define CHARACTER

#include <SDL3/SDL.h>
#include <vector>
#include "Window.h"
#include "Hitbox.h"
#include "Chunk.h"

class Character {
public:
	Character(float x, float y, float width, float height, AppWindow window);

	void handle_event(bool fullscreen);

	void move();

	void collide(std::vector<Chunk>& map);

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
	void moveJump();

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

	float xVelocity = 0;
	float yVelocity = 0;
	float jumpVelocity = 20;
	float gravity = 1;

	void set_texture(float xOffset);

	void solid_Y_collision(Tile& tile);
	void solid_X_collision(Tile& tile);
};

#endif
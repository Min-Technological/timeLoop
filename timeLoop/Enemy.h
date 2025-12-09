#pragma once
#ifndef ENEMY
#define ENEMY

#include <iostream>
#include <SDL3\SDL.h>
#include "Window.h"
#include "Time.h"
#include "Hitbox.h"
#include "Health.h"

class Enemy {
public:

	Enemy(float initialX, float initialY, AppWindow window, Time& timer, float& s, float& depth);
	void update(float xOffset, float yOffset);
	void render();

	// IDK
	Hitbox* get_hitbox();
	void take_damage(float damage);

	

private:

	void die();

	std::string nameID = "NULL";
	Hitbox hitbox;
	Renderer renderer;
	Health health;


	float spawnX, spawnY;
	float x, y, w, h;
	float newX, newY;
	float velocityX, velocityY;

	Uint8 tempR = 0x80;
	Uint8 tempB = 0xff;
	

};



#endif

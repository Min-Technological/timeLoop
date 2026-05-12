#pragma once
#ifndef ENEMY
#define ENEMY

#include <iostream>
#include <SDL3\SDL.h>
#include "Window.h"
#include "Time.h"
#include "Hitbox.h"
#include "Health.h"
#include "Enums.h"


class Enemy {
public:

	Enemy(float initialX, float initialY, AppWindow window, Time& timer, float& s, float& depth);
	void update(float xOffset, float yOffset);
	void render();

	// IDK
	Hitbox* get_hitbox();
	void take_damage(float damage);

	float get_contact();

	void enable_interaction(bool state, CharacterID ID);
	CharacterID get_interaction();

	std::string get_name();

	bool emitting_contact();


	

private:

	void die();
	void convert_ID_to_name(CharacterID ID);

	std::string nameID = "NULL";
	CharacterID characterID = CharacterID::NILL;
	Hitbox hitbox;
	Renderer renderer;
	Health health;

	Time& time;


	float spawnX, spawnY;
	float x, y, w, h;
	float newX, newY;
	float velocityX = 0;
	float velocityY = 0;

	Uint8 tempR = 0x80;
	Uint8 tempB = 0xff;

	bool emitContact = true;
	float contactDamage = 1;


	// === Interaction ===
	bool interactionState = false;

	

};



#endif

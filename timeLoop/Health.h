#pragma once
#ifndef HEALTH
#define HEALTH

#include "Attack.h"

class Health {
public:
	Health(int initialHalth, int invincibilityFrames);

	void damage(float damage, Uint64 currentFrame);
	void heal(int increase);

	bool get_death();
	float get_hp();

	bool is_invincible(Uint64 currentFrame);

	void revive();

private:
	float health = 1;
	int maxHealth = 1;

	bool dead = false;
	float tempDefenseVal = 1;

	Uint64 invincibility = 0;
	int invincibilityFrameCount = 10;
};




#endif

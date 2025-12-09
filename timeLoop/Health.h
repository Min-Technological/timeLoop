#pragma once
#ifndef HEALTH
#define HEALTH

#include "Time.h"
#include "Attack.h"

class Health {
public:
	Health(int initialHalth, int invincibilityFrames, Time& inputTime);

	void damage(float damage);
	void heal(int increase);

	bool get_death();
	float get_hp();

private:
	float health = 1;
	int maxHealth = 1;

	bool dead = false;
	float tempDefenseVal = 1;

	Time& time;
	Uint64 invincibility = 0;
	int invincibilityFrameCount = 10;
};




#endif

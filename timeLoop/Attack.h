#pragma once
#ifndef ATTACK
#define ATTACK

#include "Hitbox.h"

class Attack {
public:
	void set_damage(float damage);
	float get_damage();

	void set_rect_attack(float x, float y, float w, float h);

	void despawn_attack();
	Hitbox* get_attack();

private:
	Hitbox currentAttack;
	float damage = -1;
};



#endif
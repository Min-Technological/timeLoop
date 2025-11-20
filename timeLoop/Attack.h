#pragma once
#ifndef ATTACK
#define ATTACK

#include "Hitbox.h"

class Attack {
public:
	void set_damage(int damage);
	int get_damage();

	void set_rect_attack(float x, float y, float w, float h);

	void despawn_attack();
	Hitbox* get_attack();

private:
	Hitbox currentAttack;
	int damage = -1;
};



#endif
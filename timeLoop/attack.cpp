#include "Attack.h"

void Attack::set_damage(int damage) {
	this->damage = damage;
}

int Attack::get_damage() {
	return damage;
}

void Attack::set_rect_attack(float x, float y, float w, float h) {
	currentAttack.update_hitbox(x, y, w, h);
	currentAttack.enable_collisions(true);
}

void Attack::despawn_attack() {
	currentAttack.enable_collisions(false);
}

Hitbox* Attack::get_attack() {
	return &currentAttack;
}

#include "Health.h"

Health::Health(int initialHealth, int invincibilityFrames) :
	health(initialHealth),
	maxHealth(initialHealth),
	invincibilityFrameCount(invincibilityFrames)
	{
	
}



void Health::damage(float damage, Uint64 currentFrame) {

	if (invincibility + invincibilityFrameCount <= currentFrame) {

		if (!dead) {
			health -= damage;
		}

		if (health <= 0) {
			dead = true;
		}

		invincibility = currentFrame;
	}
	else {
	}
}

void Health::heal(int increase) {
	if (!dead) {
		health += increase;
		if (health > maxHealth) {
			health = maxHealth;
		}
	}
}

bool Health::get_death() {
	return dead;
}

float Health::get_hp() {
	return health;
}

bool Health::is_invincible(Uint64 currentFrame) {

	if (invincibility + invincibilityFrameCount > currentFrame) return true;

	return false;

}

void Health::revive() {
	health = static_cast<float>(maxHealth);
	dead = false;
}


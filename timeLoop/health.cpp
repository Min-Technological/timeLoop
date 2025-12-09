#include "Health.h"

Health::Health(int initialHealth, int invincibilityFrames, Time& inputTime) :
	health(initialHealth),
	maxHealth(initialHealth),
	invincibilityFrameCount(invincibilityFrames),
	time(inputTime) {
	
}



void Health::damage(float damage) {

	std::cout << "Damaging? " << invincibility + invincibilityFrameCount << " vs. " << time.current_frame() << "\n";
	if (invincibility + invincibilityFrameCount <= time.current_frame()) {

		if (!dead) {
			health -= damage;
		}

		if (health <= 0) {
			dead = true;
		}

		invincibility = time.current_frame();
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

#include "LoopData.h"

LoopData::LoopData() : passive{ PassiveData{} } {}

void LoopData::update_passive(const Character& character) {
	PassiveData newPassive;
	std::array<float, 2> velocity = character.get_velocity();
	newPassive.x = character.hitbox.xa;
	newPassive.y = character.hitbox.ya;
	newPassive.xVelocity = velocity[0];
	newPassive.yVelocity = velocity[1];

	passive.push_back(newPassive);
}

PassiveData LoopData::dump_passive_data() {
	return passive[0];
}

#include "LoopData.h"

LoopData::LoopData() : passive{ PassiveData{} } {}

void LoopData::update_passive(const Character& character, Uint64 frame) {
	PassiveData newPassive;
	std::array<float, 2> velocity = character.get_velocity();
	newPassive.x = character.hitbox.xa;
	newPassive.y = character.hitbox.ya;
	newPassive.xVelocity = velocity[0];
	newPassive.yVelocity = velocity[1];
	newPassive.provide_frame(frame);

	passive.push_back(newPassive);
	std::cout << passive.size() << "\n";
}

PassiveData LoopData::dump_passive_data() {
	if (passive.size() > cliffPoint) {
		return passive[(passive.size() - cliffPoint)];
	}
	else {
		PassiveData tempData;
		return tempData;
	}
}

Uint64 LoopData::return_passive_size() {
	return passive.size();
}

void LoopData::kull_passive_data() {
	for (PassiveData& loopPoint : passive) {
		Uint64 point = loopPoint.return_frame();
		if (point < cliffPoint) {
			std::cout << "ERASED CLIFF POINT!\n";
			passive.erase(passive.begin());
		}
		else {
			break;
		}
	}
}

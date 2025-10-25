#include "LoopData.h"

LoopData::LoopData(Uint64 sTime) :
	saveTime(sTime) {}

void LoopData::save_passive(PassiveData passiveData) {
	currentPassive = passiveData;
}
PassiveData* LoopData::load_passive() {
	return &currentPassive;
}




void LoopData::save_persona(int persona) {
	currentPersona = static_cast<Character::Persona>(persona);
}

int LoopData::load_persona() {
	return static_cast<int>(currentPersona);
}

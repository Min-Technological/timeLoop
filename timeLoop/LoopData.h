#pragma once
#ifndef LOOPDATA
#define LOOPDATA

#include <vector>
#include <array>
#include "PassiveData.h"

#include "Character.h"

class LoopData {
public:
	LoopData(Uint64 saveTime);

	void save_passive(PassiveData passiveData);
	PassiveData* load_passive();

	void save_persona(int persona);
	int load_persona();

private:

	int currentPersona = Character::Persona::PROTAG;

	// === Data Vectors ===
	PassiveData currentPassive;

	// === Private Variables
	Uint64 saveTime;
};



#endif

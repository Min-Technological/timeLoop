#pragma once
#ifndef LOOPDATA
#define LOOPDATA

#include <vector>
#include <array>
#include "PassiveData.h"

#include "Character.h"

class LoopData {
public:
	LoopData();

	void update_passive(const Character& character, Uint64 frame);
	PassiveData dump_passive_data();

	Uint64 return_passive_size();

	void kull_passive_data();
private:

	// === Data Vectors ===
	std::vector<PassiveData> passive;

	// === Private Variables
	Uint64 cliffPoint = 50;
};



#endif

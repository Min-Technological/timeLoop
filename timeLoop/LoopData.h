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

	void update_passive(const Character& character);
	PassiveData dump_passive_data();

private:
	std::vector<PassiveData> passive;
};



#endif

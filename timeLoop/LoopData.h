#pragma once
#ifndef LOOPDATA
#define LOOPDATA

#include <vector>
#include <array>
#include "Enums.h"
#include "PassiveData.h"

class LoopData {
public:
	LoopData(Uint64 saveTime);

	void save_passive(PassiveData passiveData);
	PassiveData* load_passive();

	void save_tarot_deck(std::array<bool, static_cast<int>(CardNumber::TOTAL)> deck);
	std::array<bool, static_cast<int>(CardNumber::TOTAL)> load_tarot_deck();

private:

	// === Data Vectors ===
	std::array<bool, static_cast<int>(CardNumber::TOTAL)> currentDeck = { false };
	PassiveData currentPassive;

	// === Private Variables
	Uint64 saveTime;
};



#endif

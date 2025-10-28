#pragma once
#ifndef LOOPDATA
#define LOOPDATA

#include <vector>
#include <array>
#include "PassiveData.h"

#include "Character.h"
#include "TarotDeck.h"

class LoopData {
public:
	LoopData(Uint64 saveTime);

	void save_passive(PassiveData passiveData);
	PassiveData* load_passive();

	void save_tarot_deck(TarotDeck tarotDeck);
	TarotDeck* load_tarot_deck();

private:

	// === Data Vectors ===
	PassiveData currentPassive;
	TarotDeck currentDeck;

	// === Private Variables
	Uint64 saveTime;
};



#endif

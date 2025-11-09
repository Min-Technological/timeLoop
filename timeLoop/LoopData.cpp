#include "LoopData.h"

LoopData::LoopData(Uint64 sTime) :
	saveTime(sTime) {}

void LoopData::save_passive(PassiveData passiveData) {
	currentPassive = passiveData;
}
PassiveData* LoopData::load_passive() {
	return &currentPassive;
}


void LoopData::save_tarot_deck(std::array<bool, static_cast<int>(CardNumber::TOTAL)> deck) {
	currentDeck = deck;
}
std::array<bool, static_cast<int>(CardNumber::TOTAL)> LoopData::load_tarot_deck() {
	return currentDeck;
}



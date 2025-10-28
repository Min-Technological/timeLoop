#include "LoopData.h"

LoopData::LoopData(Uint64 sTime) :
	saveTime(sTime) {}

void LoopData::save_passive(PassiveData passiveData) {
	currentPassive = passiveData;
}
PassiveData* LoopData::load_passive() {
	return &currentPassive;
}


void LoopData::save_tarot_deck(TarotDeck tarotDeck) {
	currentDeck = tarotDeck;
}
TarotDeck* LoopData::load_tarot_deck() {
	return &currentDeck;
}



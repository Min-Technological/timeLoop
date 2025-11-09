#pragma once
#ifndef TAROTDECK
#define TAROTDECK

#include <array>
#include <vector>
#include "TarotCard.h"
#include "loopData.h"

class TarotDeck {
public:
	void add_card(CardNumber card);
	void remove_card(CardNumber card);
	bool has_card(CardNumber card);

	void save_cards(LoopData* loopData);
	void load_cards(LoopData* loopData);

	std::vector<CardNumber> found_cards();
	std::vector<CardNumber> lost_cards();

	void evaporate_card(TarotCard* realCard);

private:
	std::vector<CardNumber> get_cards(bool type);

	std::array<bool, static_cast<int>(CardNumber::TOTAL)> deck { false };

	CardNumber past = static_cast<CardNumber>(0);
	CardNumber present = static_cast<CardNumber>(0);
	CardNumber future = static_cast<CardNumber>(0);

};

#endif

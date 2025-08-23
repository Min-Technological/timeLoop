#pragma once
#ifndef TAROTDECK
#define TAROTDECK

#include <array>
#include <vector>
#include "TarotCard.h"

class TarotDeck {
public:
	void add_card(TarotCard::CardNumber card);
	void remove_card(TarotCard::CardNumber card);
	bool has_card(TarotCard::CardNumber card);
	std::vector<TarotCard::CardNumber> found_cards();
	std::vector<TarotCard::CardNumber> lost_cards();

	void evaporate_card(TarotCard* realCard);

private:
	std::vector<TarotCard::CardNumber> get_cards(bool type);

	std::array<bool, static_cast<int>(TarotCard::CardNumber::TOTAL)> deck { false };

	TarotCard::CardNumber past;
	TarotCard::CardNumber present;
	TarotCard::CardNumber future;

};

#endif

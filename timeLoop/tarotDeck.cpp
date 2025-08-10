#include "TarotDeck.h"

void TarotDeck::add_card(TarotCard::CardNumber card) {
	deck[static_cast<int>(card)] = true;
}

void TarotDeck::remove_card(TarotCard::CardNumber card) {
	deck[static_cast<int>(card)] = false;
}

bool TarotDeck::has_card(TarotCard::CardNumber card) {
	return deck[static_cast<int>(card)];
}

std::vector<TarotCard::CardNumber> TarotDeck::found_cards() {
	return get_cards(true);
}

std::vector<TarotCard::CardNumber> TarotDeck::lost_cards() {
	return get_cards(false);
}

std::vector<TarotCard::CardNumber> TarotDeck::get_cards(bool type) {
	std::vector<TarotCard::CardNumber> hasList;
	for (int i = 0; i < static_cast<int>(TarotCard::CardNumber::TOTAL); i++) {
		if (deck[i] != type) {
			continue;
		}

		hasList.push_back(static_cast<TarotCard::CardNumber>(i));
	}

	return hasList;
}

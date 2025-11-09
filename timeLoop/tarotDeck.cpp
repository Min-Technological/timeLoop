#include "TarotDeck.h"

void TarotDeck::add_card(CardNumber card) {
	deck[static_cast<int>(card)] = true;
}

void TarotDeck::remove_card(CardNumber card) {
	deck[static_cast<int>(card)] = false;
}

bool TarotDeck::has_card(CardNumber card) {
	return deck[static_cast<int>(card)];
}

void TarotDeck::save_cards(LoopData* loopData) {
	loopData->save_tarot_deck(deck);
}

void TarotDeck::load_cards(LoopData* loopData) {
	deck = loopData->load_tarot_deck();
}

std::vector<CardNumber> TarotDeck::found_cards() {
	return get_cards(true);
}

std::vector<CardNumber> TarotDeck::lost_cards() {
	return get_cards(false);
}

std::vector<CardNumber> TarotDeck::get_cards(bool type) {
	std::vector<CardNumber> hasList;
	for (int i = 0; i < static_cast<int>(CardNumber::TOTAL); i++) {
		if (deck[i] != type) {
			continue;
		}

		hasList.push_back(static_cast<CardNumber>(i));
	}

	return hasList;
}

void TarotDeck::evaporate_card(TarotCard* realCard) {
	add_card(realCard->get_card_number());
	realCard->destroy();
}

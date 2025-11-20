#include "TarotCard.h"

TarotCard::TarotCard(int cardType, float X, float Y, AppWindow appWindow, float& s, float& depth) :
	cardNumber(static_cast<CardNumber>(cardType)), hitbox(X, Y - 40, w, h), renderer(appWindow.get_renderer(), X, Y - 40,  w, h, s, depth), x(X), y(Y - 40) {
    renderer.load_texture("tarotCards.png");
}

void TarotCard::update(float offset) {
    renderer.new_position(x, y, w, h, offset);

}

void TarotCard::render(std::vector<float> screenDimensions) {
	if (!cardCollected && renderer.test_frame(screenDimensions)) {
		renderer.render_sprite(static_cast<float>(cardNumber) * 86, 0.0f, 86.0f, 172.0f);

	}
}

Hitbox* TarotCard::get_hitbox() {
	return &hitbox;
}

CardNumber TarotCard::get_card_number() const {
	return cardNumber;
}

std::string TarotCard::get_card_name() const {

    switch (cardNumber) {
	case CardNumber::FOOL:
		return "Fool";
		break;

	case CardNumber::MAGICIAN:
		return "Magician";
		break;

	case CardNumber::HIGH_PRIESTESS:
		return "High Priestess";
		break;

	case CardNumber::EMPRESS:
		return "Empress";
		break;

	case CardNumber::EMPEROR:
		return "Emperor";
		break;

	case CardNumber::HIGH_PRIEST:
		return "High Priest";
		break;

	case CardNumber::LOVERS:
		return "Lovers";
		break;

	case CardNumber::CHARIOT:
		return "Chariot";
		break;

	case CardNumber::STRENGTH:
		return "Strength";
		break;

	case CardNumber::HERMIT:
		return "Hermit";
		break;

	case CardNumber::WHEEL_OF_FORTUNE:
		return "Wheel of Fortune";
		break;

	case CardNumber::JUSTICE:
		return "Justice";
		break;

	case CardNumber::HANGED_MAN:
		return "Hanged Man";
		break;

	case CardNumber::DEATH:
		return "Death";
		break;

	case CardNumber::TEMPERANCE:
		return "Temperance";
		break;

	case CardNumber::DEVIL:
		return "Devil";
		break;

	case CardNumber::TOWER:
		return "Tower";
		break;

	case CardNumber::STAR:
		return "Star";
		break;

	case CardNumber::MOON:
		return "Moon";
		break;

	case CardNumber::SUN:
		return "Sun";
		break;

	case CardNumber::JUDGEMENT:
		return "Judgement";
		break;

	case CardNumber::WORLD:
		return "World";
		break;

	default:
		return "CARD NAME ERROR!";
		break;
    }
}

void TarotCard::collect(bool state) {
	cardCollected = state;
}

bool TarotCard::collected() {
	return cardCollected;
}

void TarotCard::destroy() {
    renderer.destroy_texture();
    cardCollected = true;
}
#include "TarotCard.h"

TarotCard::TarotCard(int cardType, float X, float Y, AppWindow appWindow, float& s) :
	cardNumber(static_cast<CardNumber>(cardType)), hitbox(X, Y - 40, w, h), renderer(appWindow.get_renderer(), X, Y - 40,  w, h, s), x(X), y(Y - 40) {
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

TarotCard::CardNumber TarotCard::get_card_number() const {
	return cardNumber;
}

std::string TarotCard::get_card_name() const {
    switch (cardNumber) {
	case FOOL:
		return "Fool";
		break;

	case MAGICIAN:
		return "Magician";
		break;

	case HIGH_PRIESTESS:
		return "High Priestess";
		break;

	case EMPRESS:
		return "Empress";
		break;

	case EMPEROR:
		return "Emperor";
		break;

	case HIGH_PRIEST:
		return "High Priest";
		break;

	case LOVERS:
		return "Lovers";
		break;

	case CHARIOT:
		return "Chariot";
		break;

	case STRENGTH:
		return "Strength";
		break;

	case HERMIT:
		return "Hermit";
		break;

	case WHEEL_OF_FORTUNE:
		return "Wheel of Fortune";
		break;

	case JUSTICE:
		return "Justice";
		break;

	case HANGED_MAN:
		return "Hanged Man";
		break;

	case DEATH:
		return "Death";
		break;

	case TEMPERANCE:
		return "Temperance";
		break;

	case DEVIL:
		return "Devil";
		break;

	case TOWER:
		return "Tower";
		break;

	case STAR:
		return "Star";
		break;

	case MOON:
		return "Moon";
		break;

	case SUN:
		return "Sun";
		break;

	case JUDGEMENT:
		return "Judgement";
		break;

	case WORLD:
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
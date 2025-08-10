#include "TarotCard.h"

TarotCard::TarotCard(int cardType, float X, float Y, AppWindow appWindow) :
	cardNumber(static_cast<CardNumber>(cardType)), hitbox(X, Y - 40, 10, 10), renderer(appWindow.get_renderer(), X, Y - 40,  10, 20), x(X), y(Y - 40) {
    renderer.load_texture("tarotCards.png");
}

void TarotCard::update(float viewScale, float offset) {
    if (scale != viewScale) {
        scale = viewScale;
        renderer.new_scale(scale);
    }

    renderer.new_position(x - offset, y, w, h);

}

void TarotCard::render(std::vector<float> screenDimensions) {
	if (!collected && renderer.test_frame(screenDimensions)) {
        renderer.render_sprite(cardNumber * 86, 0, 86, 172);

	}
}

TarotCard::CardNumber TarotCard::get_card_number() {
	return cardNumber;
}
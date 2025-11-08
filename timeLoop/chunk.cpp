#include "Chunk.h"

// === Constructor ===
Chunk::Chunk(float leftEdge, AppWindow window, float& s) :
    hitbox(leftEdge, 0, 640, 1080), x(leftEdge),
    renderer(window.get_renderer(), leftEdge, 0, 640, 1080, s) {
}

// === Manage Tiles ===
void Chunk::append(Tile::TileType type, float x, float y, SDL_Renderer* renderer, float& s) {
    chunk.emplace_back(type, x, y, renderer, s);
}

// === Manage Tarot Cards ===
void Chunk::add_cards(int type, float x, float y, AppWindow appWindow, float& s) {
    TarotCard* newCard = new TarotCard(type, x, y, appWindow, s);
    cards.push_back(newCard);
}

void Chunk::remove_card(TarotCard* tarotCard) {
    for ( int i = 0; i < cards.size(); i++ ) {
        TarotCard* currentTarot = cards[i];
        if (currentTarot->get_card_number() == tarotCard->get_card_number()) {
            std::cout << currentTarot->get_card_name() << "\n";
            cards.erase(cards.begin() + i);
        }
    }
}

// === Update Tiles ===
void Chunk::update(float viewScale, float offset) {
    if (scale != viewScale) {
        scale = viewScale;
    }

    renderer.new_position(x, y, w, h, offset);

    for (Tile& tile : chunk) {
        tile.update(offset);
    }
    for (TarotCard* card : cards) {
        card->update(offset);
    }
}

// === Render Tiles & Bounding Box ===
void Chunk::render(std::vector<float> screenDimensions) {
    if (renderer.test_frame(screenDimensions)) {
        for (Tile& tile : chunk) {
            tile.render(screenDimensions);
        }
        for (TarotCard* card : cards) {
            card->render(screenDimensions);
        }
    }

    if (showBounding) {
        hitbox.set_bounding_green(debug);
        hitbox.render(&renderer);
    }
}

// === Debug Helpers ===
void Chunk::set_debug(char a) {
    switch (a) {
    case 'G':
        debug = 255;
        break;
    default:
        debug = 0;
        break;
    }
}

Hitbox* Chunk::get_hitbox() {
    return &hitbox;
}


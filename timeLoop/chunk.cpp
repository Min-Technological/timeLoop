#include "Chunk.h"

// === Constructor ===
Chunk::Chunk(float leftEdge, AppWindow window) :
    hitbox(leftEdge, 0, 640, 1080), x(leftEdge),
    renderer(window.get_renderer(), leftEdge, 0, 640, 1080) {
}

// === Manage Tiles ===
void Chunk::append(Tile::TileType type, float x, float y, SDL_Renderer* renderer) {
    chunk.emplace_back(type, x, y, renderer);
}

// === Manage Tarot Cards ===
void Chunk::add_cards(int type, float x, float y, AppWindow appWindow) {
    cards.emplace_back(type, x, y, appWindow);
}

void Chunk::remove_card(TarotCard* tarotCard) {
    for ( int i = 0; i < cards.size(); i++ ) {
        TarotCard* currentTarot = &cards[i];
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
        renderer.new_scale(scale);
    }

    renderer.new_position(x, y, w, h, offset);

    for (Tile& tile : chunk) {
        tile.update(viewScale, offset);
    }
    for (TarotCard& card : cards) {
        card.update(viewScale, offset);
    }
}

// === Render Tiles & Bounding Box ===
void Chunk::render(std::vector<float> screenDimensions) {
    if (renderer.test_frame(screenDimensions)) {
        for (Tile& tile : chunk) {
            tile.render(screenDimensions);
        }
        for (TarotCard& card : cards) {
            card.render(screenDimensions);
        }
    }

    if (showBounding) {
        renderer.render_hitbox(hitbox, debug);
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

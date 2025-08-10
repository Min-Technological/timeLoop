#include "Chunk.h"

// === Constructor ===
Chunk::Chunk(float leftEdge, AppWindow window) :
    hitbox(leftEdge, 0, 640, 1080),
    r(window.get_renderer()) {
}

// === Manage Tiles ===
void Chunk::append(Tile::TileType type, float x, float y, SDL_Renderer* renderer) {
    chunk.emplace_back(type, x, y, renderer);
}

// === Manage Tarot Cards ===
void Chunk::add_cards(int type, float x, float y, AppWindow appWindow) {
    cards.emplace_back(type, x, y, appWindow);
}

// === Update Tiles ===
void Chunk::update(float viewScale, float xOffset) {
    scale = viewScale;
    xOff = xOffset;

    for (Tile& tile : chunk) {
        tile.update(viewScale, xOffset);
    }
    for (TarotCard& card : cards) {
        card.update(viewScale, xOffset);
    }
}

// === Render Tiles & Bounding Box ===
void Chunk::render(std::vector<float> screenDimensions) {
    if ((hitbox.xb - xOff) * scale >= 0 &&
        (hitbox.xa - xOff) * scale < screenDimensions[0]) {
        for (Tile& tile : chunk) {
            tile.render(screenDimensions);
        }
        for (TarotCard& card : cards) {
            card.render(screenDimensions);
        }
    }

    if (showBounding) {
        hitbox.render_hitbox(r, xOff, scale, debug);
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

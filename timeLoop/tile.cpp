#include "Tile.h"

// === Constructor ===
Tile::Tile(TileType tileType, float xPos, float yPos, SDL_Renderer* r) :
    x(xPos), y(yPos), type(tileType), renderer(r, xPos, yPos, w, w) {
    hitbox = Hitbox(xPos, yPos, w, w);
}

// === Event handler (empty) ===
void Tile::handle_event(bool fullscreen) {
}

// === Update position and scale ===
void Tile::update(float viewScale, float offset) {
    if (scale != viewScale) {
        scale = viewScale;
        renderer.new_scale(scale);
    }

    renderer.new_position(x, y, w, w, offset);

}

// === Render tile based on type and visibility ===
void Tile::render(std::vector<float> screenDimensions) {
    if (renderer.test_frame(screenDimensions)) {
        switch (type) {

        // ==== TERRAIN ====

        case TileType::DIRT_DARK:
            renderer.render_colour(125, 41, 78, 0xFF);
            break;

        case TileType::DIRT_LIGHT:
            renderer.render_colour(152, 52, 96, 0xFF);
            break;

        case TileType::GRASS_DARK:
            renderer.render_colour(195, 68, 125, 0xFF);
            break;

        case TileType::GRASS_LIGHT:
            renderer.render_colour(224, 80, 144, 0xFF);
            break;

        // === CHARACTER SWAPPER ===
        case TileType::CHARACTERSWAP_PROTAG:
            renderer.render_colour(0xC6, 0xD5, 0xFF, 0xFF);
            break;

        case TileType::CHARACTERSWAP_WAND:
            renderer.render_colour(0xFF, 0xC9, 0xB7, 0xFF);
            break;


        case TileType::NILL:
            renderer.render_colour(0x00, 0x00, 0x00, 0xFF);
            break;
        }
    }
}

// === Get numeric type value ===
int Tile::get_type() const {
    return static_cast<int>(type);
}

#include "Tile.h"

// === Constructor ===
Tile::Tile(TileType tileType, float xPos, float yPos, AppWindow window) :
    x(xPos), y(yPos), type(tileType), r(window.get_renderer()) {

    hitbox = Hitbox(xPos, yPos, w, w);
    fullscreenScale = SDL_GetWindowDisplayScale(window.get_window());
    set_texture();

    // Example for disabling collisions (commented out)
    // switch (type) {
    // case TileType::DIRT_DARK:
    //     hitbox.enable_collisions(false);
    //     break;
    // }
}

// === Event handler (empty) ===
void Tile::handle_event(bool fullscreen) {
}

// === Update position and scale ===
void Tile::update(float viewScale, float offset) {
    renderX = x - offset;
    scale = viewScale;

    if (scale != viewScale) {
        std::cout << scale << "\n";
    }

    set_texture();
}

// === Render tile based on type and visibility ===
void Tile::render(std::vector<float> screenDimensions) {
    if (x > -renderW && renderX < screenDimensions[0] &&
        y > -renderW && renderY < screenDimensions[1]) {

        switch (type) {
        case TileType::DIRT_DARK:
            SDL_SetRenderDrawColor(r, 0xDD, 0x55, 0x00, 0xFF);
            SDL_RenderFillRect(r, &t);
            break;

        case TileType::DIRT_LIGHT:
            SDL_SetRenderDrawColor(r, 0xFF, 0x66, 0x00, 0xFF);
            SDL_RenderFillRect(r, &t);
            break;

        case TileType::GRASS_DARK:
            SDL_SetRenderDrawColor(r, 0x00, 0xDD, 0x00, 0xFF);
            SDL_RenderFillRect(r, &t);
            break;

        case TileType::GRASS_LIGHT:
            SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0xFF);
            SDL_RenderFillRect(r, &t);
            break;

        case TileType::NILL:
            SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(r, &t);
            break;
        }
    }
}

// === Get numeric type value ===
int Tile::get_type() {
    return int(type);
}

// === Calculate scaled texture rect ===
void Tile::set_texture() {
    renderX = renderX * scale;
    renderY = y * scale;
    renderW = w * scale;

    t = { renderX, renderY, renderW, renderW };
}

#include "Background.h"

// === Constructor ===
Background::Background(SDL_Renderer* r) : renderer(r, 0, 0, 1920, 1080) {}

// === Update ===
void Background::update(int screenW, int screenH, int gameState) {
    renderer.new_position(0, 0, static_cast<float>(screenW), static_cast<float>(screenH), 0);
    if (newState != gameState) {
        newState = gameState;
        switch (newState) {
        case 0: // MENU
            break;
        case 1: // GAME
            break;
        case 2: // PAUSE
            break;
        case 3: // SUICIDE
            renderer.load_texture("suicideNone.png");
            break;
        case 4: // REWIND
            break;
        case 5: // TAROT
            break;
        default:
            std::cout << "SOMETHING WENT WRONG, BACKGROUND STATE\n";
            break;
        }
    }
}

// === Render ===
void Background::render() {
    switch (newState) {
    case 0: // MENU
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);
        break;
    case 1: // GAME
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);
        break;
    case 2: // PAUSE
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);
        break;
    case 3: // SUICIDE
        renderer.render_texture();
        break;
    case 4: // REWIND
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);
        break;
    case 5: // TAROT
        renderer.render_colour(0x50, 0xe0, 0xa0, 0xff);
        break;
    default:
        std::cout << "SOMETHING WENT WRONG, BACKGROUND STATE\n";
        break;
    }

}

#include "Background.h"

// === Constructor ===
Background::Background(SDL_Renderer* r, float& s) : renderer(r, 0, 0, 1920, 1080, s) {}

// === Update ===
void Background::update(int screenW, int screenH, int gameState) {
    renderer.new_position(0, 0, 1920, 1080, 0);
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
        case 5: // TAROTREADER
            renderer.load_texture("tarotBasic.png");
            break;
        case 6: // TAROTCARDS
            renderer.load_texture("tarotSelect.png");
            break;
        default:
            std::cout << "SOMETHING WENT WRONG, BACKGROUND UPDATE\n";
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
    case 5: // TAROTREADER
        renderer.render_texture();
        break;
    case 6: // TAROTCARDS
        renderer.render_texture();
        break;
    default:
        std::cout << "SOMETHING WENT WRONG, BACKGROUND RENDER\n";
        break;
    }

}

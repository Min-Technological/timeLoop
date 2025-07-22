#include "Background.h"

// === Constructor ===
Background::Background(SDL_Renderer* renderer) : r(renderer) {}

// === Event Handling ===
void Background::handle_event(bool fullscreenState) {
    if (fullscreenState) {
        v.w = 1920;
        v.h = 1080;
    }
    else {
        v.w = 960;
        v.h = 540;
    }
}

// === Update ===
void Background::update(int screenW, int screenH, int gameState) {
    v.w = screenW;
    v.h = screenH;

    switch (gameState) {
    case 0: // MENU
        destroy_texture();
        break;
    case 1: // GAME
        destroy_texture();
        break;
    case 2: // PAUSE
        destroy_texture();
        break;
    case 3: // SUICIDE
        destroy_texture();
        load_texture("suicide.png");
        break;
    case 4: // REWIND
        destroy_texture();
        break;
    case 5: // TAROT
        destroy_texture();
        break;
    default:
        std::cout << "SOMETHING WENT WRONG, BACKGROUND STATE\n";
        break;
    }
}

// === Render ===
void Background::render() {
    if (t == nullptr) {
        SDL_SetRenderDrawColor(r, 0x50, 0xE0, 0xA0, 0xFF);
        SDL_RenderFillRect(r, &v);
        return;
    }

    SDL_RenderTexture(r, t, NULL, &v);

}

// === Loading Background Texture ===
void Background::load_texture(const std::string& path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        std::cout << "UNABLE TO LOAD IMAGE! " << SDL_GetError() << std::endl;
        return;
    }

    t = SDL_CreateTextureFromSurface(r, loadedSurface);
    if (!t) {
        std::cout << "UNABLE TO CREATE TEXTURE FROM: " << SDL_GetError() << std::endl;
    }
    else {
        SDL_SetTextureScaleMode(t, SDL_SCALEMODE_NEAREST);
    }



    SDL_DestroySurface(loadedSurface);

}

void Background::destroy_texture() {
    if (t) {
        SDL_DestroyTexture(t);
        t = nullptr;
    }
}

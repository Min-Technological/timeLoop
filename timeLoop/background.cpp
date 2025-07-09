#include "Background.h"

// === Constructor ===
Background::Background(SDL_Renderer* renderer) : r(renderer) {}

// === Event Handling ===
void Background::handle_event(bool fullscreenState) {
    if (fullscreenState) {
        t.w = 1920;
        t.h = 1080;
    }
    else {
        t.w = 960;
        t.h = 540;
    }
}

// === Update ===
void Background::update(int screenW, int screenH) {
    t.w = screenW;
    t.h = screenH;
}

// === Render ===
void Background::render() {
    SDL_SetRenderDrawColor(r, 0x50, 0xE0, 0xA0, 0xFF);
    SDL_RenderFillRect(r, &t);
}

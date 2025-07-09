#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include <SDL3/SDL.h>

class Background {
public:
    // === Constructor ===
    Background(SDL_Renderer* renderer);

    // === Public Methods ===
    void handle_event(bool fullscreenState);
    void update(int screenW, int screenH);
    void render();

private:
    // === Fields ===
    SDL_FRect t = { 0, 0, 960, 540 }; // Texture rect
    SDL_Renderer* r;                  // Renderer
};

#endif

#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include <iostream>
#include <SDL3/SDL.h>
#include "Renderer.h"

class Background {
public:
    // === Constructor ===
    Background(SDL_Renderer* r, float& s);

    // === Public Methods ===
    void handle_event(bool fullscreenState);
    void update(int screenW, int screenH, int gameState);
    void render();

private:
    // === Fields ===
    Renderer renderer;
    int newState = 0;

};

#endif

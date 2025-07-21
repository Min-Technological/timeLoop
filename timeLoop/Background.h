#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image\SDL_image.h>

class Background {
public:
    // === Constructor ===
    Background(SDL_Renderer* renderer);

    // === Public Methods ===
    void handle_event(bool fullscreenState);
    void update(int screenW, int screenH, int gameState);
    void render();

private:
    // === Fields ===
    SDL_FRect v = { 0, 0, 960, 540 }; // Texture Viewport
    SDL_Renderer* r;                  // Renderer
    SDL_Texture* t = nullptr;

    // === Helper Functions ===
    void load_texture(const std::string& path);
    void destroy_texture();

};

#endif

#pragma once
#ifndef TITLEBAR
#define TITLEBAR

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <stdio.h>
#include <functional>

#include "Window.h"

class Titlebar {
public:
    // === Constructor ===
    Titlebar(int width, int height, std::string buttonTextures, SDL_Renderer* renderer, AppWindow* appWindow);

    // === Public Methods ===
    void load_texture(std::string texturePath);
    void load_sprites(SDL_FRect button[], int column);
    void handle_event(SDL_Event* e);
    void handle_minimise(SDL_Event* e);
    void handle_fullscreen(SDL_Event* e);
    void handle_close(SDL_Event* e);
    void set_state(int state1, int state2, int state3);
    void render();
    void destroy();

    // === Public Fields ===
    int titleHeight;

private:
    // === Dimensions ===
    int titleWidth;

    // === Window & Renderer ===
    AppWindow* titleBarWindow;
    SDL_Renderer* titleBarRenderer;
    SDL_Texture* titleBarTexture;

    // === Render State ===
    SDL_Rect renderWindow = { 0, titleHeight, 960, 540 };

    SDL_FRect minimiseSprites[3];
    SDL_FRect fullscreenSprites[3];
    SDL_FRect closeSprites[3];

    int minimiseState = 0;
    int fullscreenState = 0;
    int closeState = 0;

    bool isClicking = false;

    // === Button Constants ===
    const float buttonWidth = 48;
    const float buttonHeight = 25;
};

#endif

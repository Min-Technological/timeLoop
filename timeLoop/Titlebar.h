#pragma once
#ifndef TITLEBAR
#define TITLEBAR

#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <array>

#include "Window.h"
#include "Renderer.h"
#include "Input.h"

class Titlebar {
public:
    // === Constructor ===
    Titlebar(int width, int height, std::string buttonTextures, SDL_Renderer* renderer, AppWindow* appWindow);

    // === Public Methods ===
    void handle_event(Input input);
    void handle_minimise(const SDL_Event &e);
    void handle_fullscreen(const SDL_Event &e);
    void handle_close(const SDL_Event &e);
    void set_state(int state1, int state2, int state3);
    void render();
    void destroy();

    // === Public Fields ===
    int titleWidth;
    int titleHeight;

private:

    // === Window & Renderer ===
    AppWindow* titleBarWindow;
    Renderer renderer;

    std::array<int, 3> states = { 0, 0 ,0 };

    bool isClicking = false;

    // === Button Constants ===
    const float buttonWidth = 48;
    const float buttonHeight = 25;
    float dummyValue = 1.0f;
};

#endif

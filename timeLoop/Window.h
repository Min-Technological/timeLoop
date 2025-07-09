#pragma once
#ifndef WINDOW
#define WINDOW

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

class AppWindow {
public:
    // === Constructor ===
    AppWindow(std::string title, int width, int height, int titleHeight);

    // === Public Methods ===
    SDL_Window* get_window();
    SDL_Renderer* get_renderer();
    static SDL_HitTestResult windowHitTest(SDL_Window* win, const SDL_Point* pos, void* data);

    void fullscreen();
    void windowed();
    bool is_fullscreen() const;

    void close();
    bool is_running() const;
    void destroy();

private:
    // === Window Properties ===
    std::string windowTitle;
    int windowWidth;
    int windowHeight;
    int windowTitleBar;
    bool fullScreen = false;
    bool windowRunning = true;

    // === SDL Handles ===
    SDL_Window* mainWindow = nullptr;
    SDL_Renderer* mainRenderer = nullptr;

    // === Private Helpers ===
    void create_window(Uint16 windowArgs);
    void create_renderer();
};

#endif

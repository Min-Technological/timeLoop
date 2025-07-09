#pragma once
#ifndef GAMESTATE
#define GAMESTATE

#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>

#include "Window.h"
#include "Titlebar.h"
#include "Time.h"
#include "Chunk.h"
#include "Background.h"
#include "Character.h"
#include "Camera.h"
#include "Map.h"

class Gamestate {
public:
    // === Constructor ===
    Gamestate();

    // === Public Fields ===
    bool quit;

    // === Game Loop Functions ===
    void initialise_map();
    void set_render_canvas();
    void handle_event();
    void move();
    void update();
    void render();

    // === Exit Game Functions ===
    void close();

    // === Game State Management ===
    enum State {
        MENU,
        GAME
    };

    State currentState = State::GAME;
    State get_current_state();
    void change_state();

private:
    // === Private Helpers ===
    void calculate_scale();

    // === Subsystems ===
    AppWindow window;
    Titlebar titlebar;
    Time time;
    Background background;
    Character user;
    Camera camera;
    Map gameMap0;

    // === Input & Map ===
    SDL_Event event{};
    std::vector<Chunk> currentMap;

    // === Display State ===
    int screenW = 1920;
    int windowH = 1080;
    int screenH = 1080;
    float scale = 1.0f;
};

#endif

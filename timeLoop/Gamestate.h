#pragma once
#ifndef GAMESTATE
#define GAMESTATE

#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>

#include "Window.h"
#include "Titlebar.h"
#include "Input.h"
#include "Time.h"
#include "Chunk.h"
#include "Background.h"
#include "Character.h"
#include "Camera.h"
#include "Map.h"
#include "LoopData.h"

class Gamestate {
public:
    // === Constructor ===
    Gamestate();

    // === Public Fields ===
    bool quit;
    Uint64 frameCount = 0;

    // === Game Loop Functions ===
    void initialise_map();
    void set_render_canvas();
    void handle_event();
    void move();
    void update();
    void render();

    // === Pause Loop Functions ===
    void pause_render();

    // === Suicide Loop Functions ===
    void suicide_update();
    void suicide_render();

    // === Cleanup ===
    void increment_frame();
    void close();

    // === Game State Management ===
    enum State {
        MENU,
        GAME,
        PAUSE,
        SUICIDE,
        REWIND,
        TAROT,
        TOTAL
    };
    State currentState = State::GAME;
    State get_current_state() const;
    void change_state();
    void print_state() const;

    // === Loop Management ===
    void update_loop_data();

private:
    // === Private Helpers ===
    void calculate_scale();
    void increment_loop_data();

    // === Subsystems ===
    AppWindow window;
    Titlebar titlebar;
    Input input;
    Time time;
    Background background;
    Character user;
    Camera camera;
    Map gameMap0;
    LoopData loopData;

    // === Input & Map ===
    SDL_Event event{};
    std::vector<Chunk> currentMap;

    // === Display State ===
    int screenW = 1920;
    int windowH = 1080;
    int screenH = 1080;
    float scale = 1.0f;
    bool bounding = false;

    // === Uh... Memory ===
    bool waiting = false;
    Uint64 waitTime = 0;
    Uint64 loopTime = 0;
};

#endif

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
#include "Background.h"
#include "Character.h"
#include "Camera.h"
#include "Map.h"
#include "Chunk.h"
#include "TarotDeck.h"
#include "LoopData.h"
#include "CharacterSelect.h"
#include "TarotReader.h"
#include "Enums.h"
#include "Collisions.h"

class Gamestate {
public:
    // === Constructor ===
    Gamestate();

    // === Game Loop Functions ===
    void initialise_map();
    void set_render_canvas();
    void handle_event();
    void move();
    void update();
    void render();
    void render_hitbox();

    // === Pause Loop Functions ===
    void pause_update();
    void pause_render();

    // === Suicide Loop Functions ===
    void suicide_update();
    void suicide_render();

    // === Selection Functions ===
    void selection_update();
    void selection_render();

    // === Tarot Reading Loop Functions ===
    void tarot_update();
    void tarot_render();

    // === Cleanup ===
    void increment_frame();
    void close();

    // === Loop Management ===
    void save_loop_data();
    void load_loop_data();

    // === Game State Helpers ===
    State get_current_state() const;
    void change_state();
    void print_state() const;

    // === Quit Status ===
    bool get_quit();

private:

    // === Public Fields ===
    bool quit;
    Uint64 frameCount = 0;

    // === Game State Management ===
    State currentState = State::TAROTREADING;

    // === Private Helpers ===
    void calculate_scale();

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
    CharacterSelect characterSelect;
    TarotReader tarotScene;
    Collisions collisionManager;
    TarotDeck tarotDeck;

    // === Input & Map ===
    SDL_Event event{};
    std::vector<Chunk> currentMap;
    std::array<TarotCard*, static_cast<int>(CardNumber::TOTAL)> tarotCards = { nullptr };

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

    bool charChange = false;
};

#endif

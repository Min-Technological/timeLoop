#include "Gamestate.h"

// === Constructor ===
Gamestate::Gamestate() :
    window("Test Window", 960, 540, 25),
    titlebar(960, 25, "titleBarIcons.png", window.get_renderer(), &window),
    time(60),
    background(window.get_renderer()),
    user(960, 680, 40, 80, window),
    camera(user, time, screenW, screenH, scale),
    gameMap0("map_test.png", 40, window, camera),
    quit(false)
{
    event.type = SDL_EVENT_FIRST;
    std::cout << "INITIALISED!\n";
}

// === Map Initialization ===
void Gamestate::initialise_map() {
    currentMap = gameMap0.generate_map();
}

// === Rendering Setup ===
void Gamestate::set_render_canvas() {
    SDL_Rect renderWindow;
    if (!window.is_fullscreen()) {
        renderWindow = { 0, titlebar.titleHeight, 960, 540 };
    }
    else {
        renderWindow = { 0, 0, screenW, screenH };
    }
    SDL_SetRenderViewport(window.get_renderer(), &renderWindow);
}

// === Event Handling ===
void Gamestate::handle_event() {
    while (SDL_PollEvent(&event) != 0) {
        if (!window.is_running()) {
            quit = true;
            break;
        }

        titlebar.handle_event(&event);

    }
}

// === Game Logic: Movement and Collision ===
void Gamestate::move() {
    user.move();
    user.collide(currentMap);
    camera.affect();
}

// === Game Update ===
void Gamestate::update() {
    calculate_scale();
    background.update(screenW, screenH);
    camera.update();
    user.update(scale, camera.xOffset);

    for (Chunk& chunk : currentMap) {
        chunk.update(scale, camera.xOffset);
    }
}

// === Rendering ===
void Gamestate::render() {
    SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0xFF);
    SDL_RenderClear(window.get_renderer());

    titlebar.render();
    set_render_canvas();

    background.render();

    std::vector<float> screenDimensions = { float(camera.w), float(camera.h) };
    for (Chunk& chunk : currentMap) {
        chunk.render(screenDimensions);
    }

    user.render();

    SDL_RenderPresent(window.get_renderer());
    time.sleep_delta();
}

// === Cleanup ===
void Gamestate::close() {
    titlebar.destroy();
    window.destroy();
    SDL_Quit();
}

// === State Management ===
Gamestate::State Gamestate::get_current_state() {
    return currentState;
}

void Gamestate::change_state() {
    const bool* keys = SDL_GetKeyboardState(NULL);

    if (keys[SDL_SCANCODE_ESCAPE]) {
        if (get_current_state() == State::MENU) {
            // currentState = State::GAME;
        }
        else {
            currentState = State::MENU;
        }
    }
}

// === Utility ===
void Gamestate::calculate_scale() {
    SDL_GetCurrentRenderOutputSize(window.get_renderer(), &screenW, &windowH);
    screenH = window.is_fullscreen() ? int(windowH) : int(windowH) - titlebar.titleHeight;
    scale = float(screenH) / 1080;
}

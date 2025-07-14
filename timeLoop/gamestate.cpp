#include "Gamestate.h"

// === Constructor ===
Gamestate::Gamestate() :
    window("Test Window", 960, 540, 25),
    titlebar(960, 25, "titleBarIcons.png", window.get_renderer(), &window),
    time(60),
    background(window.get_renderer()),
    user(920, 600, 40, 160, window),
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
    calculate_scale();
}

// === Game Logic: Movement and Collision ===
void Gamestate::move() {
    user.move();
    user.collide(currentMap);
    camera.affect();
}

// === Game Update ===
void Gamestate::update() {
    background.update(screenW, screenH);
    camera.update();
    user.update(scale, camera.xOffset);

    for (Chunk& chunk : currentMap) {
        chunk.update(scale, camera.xOffset);
    }
}

// === Game Rendering ===
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

// === Pause Update ===

// === Pause Rendering ===
void Gamestate::pause_render() {
    SDL_SetRenderDrawBlendMode(window.get_renderer(), SDL_BLENDMODE_BLEND);
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

    // Render Pause Overlay
    SDL_FRect v = { 0, 0, 2000, 2000 };
    SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0x5F);
    SDL_RenderFillRect(window.get_renderer(), &v);

    SDL_RenderPresent(window.get_renderer());
    time.sleep_delta();
}

// === Cleanup ===
void Gamestate::close() {
    user.destroy();
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

    if (keys[SDL_SCANCODE_F3]) {
        if (f3KeyLifted) {
            bounding = bounding ? false : true;

            user.bounding = bounding;
            for (Chunk& chunk : currentMap) {
                chunk.showBounding = bounding;
            }

            f3KeyLifted = false;
        }
    
    }
    else if (!keys[SDL_SCANCODE_F3]) {
        f3KeyLifted = true;
    }

    if (keys[SDL_SCANCODE_ESCAPE]) {
        if (escKeyLifted) {
            if (get_current_state() == State::PAUSE) {
                currentState = State::GAME;
            }
            else {
                currentState = State::PAUSE;
            }

            escKeyLifted = false;
        }
    }
    else if (!keys[SDL_SCANCODE_ESCAPE]) {
        escKeyLifted = true;
    }
}

// === Utility ===
void Gamestate::calculate_scale() {
    SDL_GetCurrentRenderOutputSize(window.get_renderer(), &screenW, &windowH);
    screenH = window.is_fullscreen() ? int(windowH) : int(windowH) - titlebar.titleHeight;
    scale = float(screenH) / 1080;
}

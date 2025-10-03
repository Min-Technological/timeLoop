#include "Gamestate.h"

// === Constructor ===
Gamestate::Gamestate() :
    window("Test Window", 960, 540, 25),
    titlebar(960, 25, "titleBarIcons.png", window.get_renderer(), &window),
    input(),
    time(60),
    background(window.get_renderer(), scale),
    user(920, 600, window, time, scale),
    camera(user, time, screenW, screenH, scale),
    gameMap0("map_test.png", 40, window, camera, scale),
    loopData(),
    tarotScene(window, scale),
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

    input.handle_event();

    quit = (input.is_event_occurring(SDL_EVENT_QUIT) ||
        window.is_running() == false) ? true : false;

    titlebar.handle_event(input);

    user.handle_event(input);
    calculate_scale();
}

// === Game Helpers ===
void Gamestate::move() {
    user.move(input);
    user.collide(currentMap);
    camera.affect(input);
}
void Gamestate::update() {
    background.update(screenW, screenH, static_cast<int>(currentState));
    camera.update();
    user.update(scale, camera.xOffset);

    for (Chunk& chunk : currentMap) {
        chunk.update(scale, camera.xOffset);
    }

    update_loop_data();

    if (input.is_key_just_pressed(SDLK_ESCAPE)) {
        currentState = State::PAUSE;
    }
}
void Gamestate::render() {
    SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0xFF);
    SDL_RenderClear(window.get_renderer());

    titlebar.render();
    set_render_canvas();

    background.render();

    std::vector<float> screenDimensions = { static_cast<float>(camera.w), static_cast<float>(camera.h) };
    for (Chunk& chunk : currentMap) {
        chunk.render(screenDimensions);
    }

    user.render();

    SDL_RenderPresent(window.get_renderer());
}

// === Pause Helpers ===
void Gamestate::pause_update() {
    background.update(screenW, screenH, static_cast<int>(currentState));
    camera.update();
    user.update(scale, camera.xOffset);

    for (Chunk& chunk : currentMap) {
        chunk.update(scale, camera.xOffset);
    }

    if (input.is_key_just_pressed(SDLK_ESCAPE)) {
        currentState = State::GAME;
    }
}
void Gamestate::pause_render() {
    SDL_SetRenderDrawBlendMode(window.get_renderer(), SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0xFF);
    SDL_RenderClear(window.get_renderer());

    titlebar.render();
    set_render_canvas();

    background.render();

    std::vector<float> screenDimensions = { static_cast<float>(camera.w), static_cast<float>(camera.h) };
    for (Chunk& chunk : currentMap) {
        chunk.render(screenDimensions);
    }

    user.render();

    // Render Pause Overlay
    SDL_FRect v = { 0, 0, static_cast<float>(screenW), static_cast<float>(screenH) };
    SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0x5F);
    SDL_RenderFillRect(window.get_renderer(), &v);

    SDL_RenderPresent(window.get_renderer());
}

// === Suicide Helpers ===
void Gamestate::suicide_update() {

    background.update(screenW, screenH, static_cast<int>(currentState));

    user.load_data(loopData.dump_passive_data());

    if (!waiting) {
        waitTime = time.current_time();
        waiting = true;
    }
    if (waiting) {
        if (time.current_time() - waitTime >= 1000) {
            currentState = State::GAME;
            waiting = false;
        }
    }

}
void Gamestate::suicide_render() {
    SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0xFF);
    SDL_RenderClear(window.get_renderer());

    titlebar.render();
    set_render_canvas();

    background.render();


    SDL_RenderPresent(window.get_renderer());
}

// === Tarot Reading Helpers ===
void Gamestate::tarot_update() {
    if (currentState == State::TAROTREADING) {
        if (tarotScene.exit_reader(input)) {
            currentState = State::GAME;
        }
    }


    background.update(screenW, screenH, static_cast<int>(currentState));

}
void Gamestate::tarot_render() {
    SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0xFF);
    SDL_RenderClear(window.get_renderer());

    titlebar.render();
    set_render_canvas();

    background.render();
    tarotScene.render(bounding);


    SDL_RenderPresent(window.get_renderer());
}

// === Cleanup ===
void Gamestate::increment_frame() {
    time.sleep_delta();
}
void Gamestate::close() {
    user.destroy();
    titlebar.destroy();
    window.destroy();
    SDL_Quit();
}

// === State Management ===
Gamestate::State Gamestate::get_current_state() const {
    return currentState;
}
void Gamestate::change_state() {

    int userState = user.return_state();
    if (currentState == State::GAME && userState != State::GAME) {
        if (userState >= 0 && userState < State::TOTAL) {
            currentState = static_cast<State>(userState);
        }
    }

    if (input.is_key_just_pressed(SDLK_F3)) {
        bounding = bounding ? false : true;

        user.bounding = bounding;
        for (Chunk& chunk : currentMap) {
            chunk.showBounding = bounding;
        }
    }

    if (get_current_state() == State::TAROTREADING) {

        // Card Selection Button
        float stainedWindowX, stainedWindowY;
        int stainedWindowW, stainedWindowH;
            stainedWindowX = 1463 * scale;
            stainedWindowY = 83 * scale;
            stainedWindowW = 342 * scale;
            stainedWindowH = 603 * scale;

        if (input.is_clicking_square(stainedWindowX, stainedWindowY, stainedWindowW, stainedWindowH)) {
            currentState = State::TAROTCARDS;
        }
    }
}

void Gamestate::print_state() const {
    std::cout << "GAMESTATE ";

    switch (currentState) {
    case State::GAME:
        std::cout << "GAME\n";
        break;
    case State::MENU:
        std::cout << "MENU\n";
        break;
    case State::PAUSE:
        std::cout << "PAUSE\n";
        break;
    case State::REWIND:
        std::cout << "REWIND\n";
        break;
    case State::SUICIDE:
        std::cout << "SUICIDE\n";
        break;
    case State::TAROTREADING:
        std::cout << "TAROTREADING\n";
        break;
    case State::TAROTCARDS:
        std::cout << "TAROTCARDS\n";
        break;
    case State::TOTAL:
        std::cout << "TOTAL\n";
        break;
    default:
        std::cout << "BLANK\n";
        break;
    }
}

// === Loop Management ===
void Gamestate::update_loop_data() {
    Uint64 currentPassiveSize = loopData.return_passive_size();
    increment_loop_data();
    if (currentPassiveSize < loopData.return_passive_size()) {
        loopData.kull_passive_data();
    }
}

void Gamestate::increment_loop_data() {
    Uint64 currentTime = time.current_time();
    if (currentTime - loopTime > 500) {
        loopData.update_passive(user, currentTime);
        loopTime = currentTime;
    }
}

// === Utility ===
void Gamestate::calculate_scale() {
    SDL_GetCurrentRenderOutputSize(window.get_renderer(), &screenW, &windowH);
    screenH = window.is_fullscreen() ? int(windowH) : int(windowH) - titlebar.titleHeight;
    scale = static_cast<float>(screenH) / 1080;
}


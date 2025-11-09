#include "Gamestate.h"

// === Constructor ===
Gamestate::Gamestate() :
    window("Test Window", 960, 540, 25),
    titlebar(960, 25, "titleBarIcons.png", window.get_renderer(), &window),
    input(),
    time(60),
    background(window.get_renderer(), scale),
    user(960, 500, window, time, scale),
    camera(user, time, screenW, screenH, scale),
    gameMap0("map_test.png", 40, window, camera, scale),
    loopData(static_cast<Uint64>(0)),
    tarotDeck(),
    characterSelect(&window, scale),
    tarotScene(window, scale),
    collisionManager(),
    quit(false)
{
    event.type = SDL_EVENT_FIRST;

    std::cout << "INITIALISED!\n";
}

// === Map Initialization ===
void Gamestate::initialise_map() {
    currentMap = gameMap0.generate_map();
    for (Chunk& chunk : currentMap) {
        for (TarotCard* card : chunk.cards) {
            tarotCards[static_cast<int>(card->get_card_number())] = card;
        }
    }
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
    SDL_SetRenderDrawBlendMode(window.get_renderer(), SDL_BLENDMODE_BLEND);
}

// === Event Handling ===
void Gamestate::handle_event() {

    input.handle_event();

    quit = (input.is_event_occurring(SDL_EVENT_QUIT) ||
        window.is_running() == false) ? true : false;

    titlebar.handle_event(input);

    calculate_scale();
}

// === Game Helpers ===
void Gamestate::move() {
    user.move(input);
    
    for (Chunk& chunk : currentMap) {
        
        if (!collisionManager.collide_character_chunk(&user, chunk.get_hitbox())) {
            chunk.get_hitbox()->set_bounding_green(0x00);
            continue;
        }

        chunk.get_hitbox()->set_bounding_green(0xff);
        for (Tile& tile : chunk.chunk) {
            collisionManager.collide_character_tile(&user, &tile);
        }
        for (TarotCard* card : chunk.cards) {
            if (card->collected()) continue;

            if (collisionManager.collide_character_card(&user, card)) {
                tarotDeck.add_card(card->get_card_number());
                card->collect(true);
            }
        }
    }

    user.resolve_collision();

    camera.affect(input);

}
void Gamestate::update() {
    background.update(screenW, screenH, currentState);
    camera.update();
    user.update(scale, camera.xOffset);

    for (Chunk& chunk : currentMap) {
        chunk.update(scale, camera.xOffset);
    }

    // update_loop_data();
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

    render_hitbox();

    SDL_RenderPresent(window.get_renderer());
}
void Gamestate::render_hitbox() {

    Renderer hitboxRenderer = Renderer(window.get_renderer(), 0, 0, 1, 1, scale);
    hitboxRenderer.set_x_offset(camera.xOffset);

    if (bounding) {
        for (Chunk& chunk : currentMap) {
            chunk.get_hitbox()->render(&hitboxRenderer);
            for (TarotCard* card : chunk.cards) {
                if (card->collected()) continue;
                card->get_hitbox()->render(&hitboxRenderer);
            }
        }
        user.get_hitbox()->render(&hitboxRenderer);
    }
}


// === Pause Helpers ===
void Gamestate::pause_update() {
    background.update(screenW, screenH, currentState);
    user.update(scale, camera.xOffset);

    for (Chunk& chunk : currentMap) {
        chunk.update(scale, camera.xOffset);
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
    background.change_persona(user.get_persona());
    background.update(screenW, screenH, currentState);

    load_loop_data();

}
void Gamestate::suicide_render() {
    SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0xFF);
    SDL_RenderClear(window.get_renderer());

    titlebar.render();
    set_render_canvas();

    background.render();


    SDL_RenderPresent(window.get_renderer());
}

// === Selection Helpers ===
void Gamestate::selection_update() {
    background.update(screenW, screenH, currentState);
    // camera.update();
    user.update(scale, camera.xOffset);

    for (Chunk& chunk : currentMap) {
        chunk.update(scale, camera.xOffset);
    }

    characterSelect.set_current_selection(user.get_persona());
    characterSelect.update(input);
    Persona characterChange = characterSelect.get_selection();
    user.change_persona(characterChange);
}
void Gamestate::selection_render() {
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

    characterSelect.render();

    SDL_RenderPresent(window.get_renderer());
}

// === Tarot Reading Helpers ===
void Gamestate::tarot_update() {


    background.update(screenW, screenH, currentState);

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
    frameCount++;
}
void Gamestate::close() {
    user.destroy();
    titlebar.destroy();
    window.destroy();
    SDL_Quit();
}

// === State Management ===
State Gamestate::get_current_state() const {
    return currentState;
}
void Gamestate::change_state() {

    switch (currentState) {
    case (State::MENU):
        break;

    case (State::GAME):
        if (input.is_key_just_pressed(SDLK_R)) {
            currentState = State::SUICIDE;
        }
        else if (input.is_key_just_pressed(SDLK_ESCAPE)) {
            currentState = State::PAUSE;
        }
        else if (input.is_key_just_pressed(SDLK_E)) {
            currentState = State::SELECTION;
        }
        // === TEMPORARY, SHOULD BE A PASSIVE THING IN GAME.UPDATE().
        else if (input.is_key_just_pressed(SDLK_F)) {
            save_loop_data();
        }
        break;

    case (State::PAUSE):
        if (input.is_key_just_pressed(SDLK_ESCAPE)) {
            currentState = State::GAME;
        }
        break;

    case (State::SUICIDE):
        if (waiting) {
            if (time.current_time() - waitTime >= 1000) {
                currentState = State::TAROTREADING;
                waiting = false;
            }
        }
        else {
            waitTime = time.current_time();
            waiting = true;
        }
        break;

    case (State::SELECTION):
        if (input.is_key_just_pressed(SDLK_E) || charChange) {
            currentState = State::GAME;
        }
        break;

    case (State::TAROTREADING):
        if (tarotScene.exit_reader(input)) {
            currentState = State::GAME;
        }
        else if (tarotScene.reading_cards(input)) {
            currentState = State::TAROTCARDS;
        }
        break;

    case (State::TAROTCARDS):
        if (tarotScene.exit_cards(input)) {
            currentState = State::TAROTREADING;
        }
        break;

    default: 
        std::cout << "CAN'T CHANGE STATE!\n";
        break;

    }



    if (input.is_key_just_pressed(SDLK_F3)) {
        bounding = bounding ? false : true;
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
void Gamestate::save_loop_data() {
    std::cout << "Saving Time Loop Data!\n";
    LoopData newLoopData(time.current_time());

    user.save_data(newLoopData.load_passive());
    camera.save_loop_data(newLoopData.load_passive());
    tarotDeck.save_cards(&newLoopData);

    loopData = newLoopData;
}
void Gamestate::load_loop_data() {
    user.load_data(loopData.load_passive());
    camera.load_loop_data(loopData.load_passive());
    tarotDeck.load_cards(&loopData);
    for (TarotCard* card : tarotCards) {
        bool collected = tarotDeck.has_card(card->get_card_number());
        if (collected) {
            card->destroy();
        }
        else {
            card->collect(false);
        }
    }
}

// === Quit Status ===
bool Gamestate::get_quit() {
    return quit;
}

// === Utility ===
void Gamestate::calculate_scale() {
    SDL_GetCurrentRenderOutputSize(window.get_renderer(), &screenW, &windowH);
    screenH = window.is_fullscreen() ? int(windowH) : int(windowH) - titlebar.titleHeight;
    scale = static_cast<float>(screenH) / 1080;
}


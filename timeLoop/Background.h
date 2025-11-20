#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include <iostream>
#include <SDL3/SDL.h>
#include "Renderer.h"
#include "Enums.h"

class Background {
public:
    // === Constructor ===
    Background(SDL_Renderer* r, float& s, float& depth);

    // === Public Methods ===
    void handle_event(bool fullscreenState);
    void update(int screenW, int screenH, State gameState);
    void render();
    void change_persona(Persona newPersona);

private:

    // === Fields ===
    Renderer renderer;
    Persona currentPersona = Persona::PROTAG;
    State newState = State::MENU;

};

#endif

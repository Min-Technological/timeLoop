#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include <iostream>
#include <SDL3/SDL.h>
#include "Renderer.h"

class Background {
public:
    // === Constructor ===
    Background(SDL_Renderer* r, float& s);

    // === Public Methods ===
    void handle_event(bool fullscreenState);
    void update(int screenW, int screenH, int gameState);
    void render();
    void change_persona(int newPersona);

private:
    enum Persona {
        PROTAG,     // No Name
        CUP,        // Zoe
        SWORD,      // Amber
        WAND,       // Velara
        PENTACLE    // Emma
    };
    Persona currentPersona = PROTAG;

    // === Fields ===
    Renderer renderer;
    int newState = 0;

};

#endif

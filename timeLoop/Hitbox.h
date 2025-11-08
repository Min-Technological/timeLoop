#pragma once
#ifndef HITBOX
#define HITBOX

#include <iostream>
#include <SDL3/SDL.h>
#include <array>

#include "Renderer.h"

class Hitbox {
public:
    // === Constructors ===
    Hitbox();
    Hitbox(float x, float y, float width, float height);

    // === Public Methods ===
    void update_hitbox(float x, float y, float width, float height);
    void change_current(float x, float y, float width, float height);
    void set_bounding_green(Uint8 debug);
    void render(Renderer *renderer);

    void enable_collisions(bool status);
    bool allows_collisions() const;

    std::array<float, 4> get_current_pos();
    std::array<float, 4> get_previous_pos();

private:

    // === Private Fields ===
    float xa; // Left Side
    float xb; // Right Side
    float ya; // Top Side
    float yb; // Bottom Side

    float previousXA; // Previous Left Side
    float previousXB; // Previous Right Side
    float previousYA; // Previous Top Side
    float previousYB; // Previous Bottom Side

    float w, h;
    bool allowsCollisions = true;
    Uint8 boundingGreen = 0x00;
};

#endif

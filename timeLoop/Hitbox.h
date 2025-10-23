#pragma once
#ifndef HITBOX
#define HITBOX

#include <iostream>
#include <SDL3/SDL.h>

class Hitbox {
public:
    // === Constructors ===
    Hitbox();
    Hitbox(float x, float y, float width, float height);

    // === Public Methods ===
    void update_hitbox(float x, float y, float width, float height);
    void enable_collisions(bool status);
    bool allows_collisions() const;

    bool check_x_collision(Hitbox& other) const;
    bool check_y_collision(Hitbox& other) const;
    bool check_collision(Hitbox& other) const;

    void destroy();

    // === Public Fields ===
    float xa; // Left Side
    float xb; // Right Side
    float ya; // Top Side
    float yb; // Bottom Side

private:
    // === Private Fields ===

    float previousXA; // Previous Left Side
    float previousXB; // Previous Right Side
    float previousYA; // Previous Top Side
    float previousYB; // Previous Bottom Side

    float w, h;
    SDL_FRect bounding;
    bool allowsCollisions = true;
};

#endif

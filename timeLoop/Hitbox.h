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
    bool check_collision(Hitbox other) const;

    // === Public Fields ===
    float xa; // Left Side
    float xb; // Right Side
    float ya; // Top Side
    float yb; // Bottom Side

private:
    // === Private Fields ===
    float w, h;
    SDL_FRect bounding;
    bool allowsCollisions = true;
};

#endif

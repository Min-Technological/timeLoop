#include "Hitbox.h"

// === Constructors ===
Hitbox::Hitbox() :
    xa(0), xb(20), ya(0), yb(40), w(1920), h(1080) {
    previousXA = xa;
    previousXB = xb;
    previousYA = ya;
    previousYB = yb;
}

Hitbox::Hitbox(float x, float y, float width, float height) :
    xa(x), ya(y), w(width), h(height) {
    xb = x + width;   // Right Edge
    yb = y + height;  // Bottom Edge

    previousXA = xa;
    previousXB = xb;
    previousYA = ya;
    previousYB = yb;
}

// === Hitbox Updates ===
void Hitbox::update_hitbox(float x, float y, float width, float height) {
    previousXA = xa;
    previousXB = xb;
    previousYA = ya;
    previousYB = yb;

    xa = x;
    xb = x + width;
    ya = y;
    yb = y + height;
}
void Hitbox::change_current(float x, float y, float width, float height) {
    xa = x;
    xb = x + width;
    ya = y;
    yb = y + height;
}

void Hitbox::set_bounding_green(Uint8 debug) {
    boundingGreen = debug;
}

void Hitbox::render(Renderer* renderer) {
    renderer->render_hitbox(xa, ya, xb, yb, boundingGreen);
    
}

// === Collision Settings ===
void Hitbox::enable_collisions(bool status) {
    allowsCollisions = status;
}

bool Hitbox::allows_collisions() const {
    return allowsCollisions;
}

std::array<float, 4> Hitbox::get_current_pos() {
    return {
        xa,
        ya,
        xb,
        yb
    };
}

std::array<float, 4> Hitbox::get_previous_pos() {
    return {
        previousXA,
        previousYA,
        previousXB,
        previousYB
    };
}
#include "Hitbox.h"

// === Constructors ===
Hitbox::Hitbox() :
    xa(0), xb(20), ya(0), yb(40), w(1920), h(1080) {
    bounding = { 0, 0, 40, 40 };
    previousXA = xa;
    previousXB = xb;
    previousYA = ya;
    previousYB = yb;
}

Hitbox::Hitbox(float x, float y, float width, float height) :
    xa(x), ya(y), w(width), h(height) {
    xb = x + width;   // Right Edge
    yb = y + height;  // Bottom Edge

    bounding = { x, y, width, height };
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

// === Collision Settings ===
void Hitbox::enable_collisions(bool status) {
    allowsCollisions = status;
}

bool Hitbox::allows_collisions() const {
    return allowsCollisions;
}

bool Hitbox::check_x_collision(Hitbox& other) const {
    if (other.allows_collisions()) {

        if (xa > previousXA) {
            if (xb > other.xa && previousXB < other.xb) return true;
        }
        else if (xa < previousXA) {
            if (previousXA > other.xb &&
                xa < other.xb) return true;
        }
    }
    else return false;
}

bool Hitbox::check_y_collision(Hitbox& other) const {
    if (other.allows_collisions()) {

        if (ya > previousYA) {
            if (yb > other.ya && previousYB < other.yb) return true;
        }
        else if (ya < previousYA) {
            if (previousYA > other.yb &&
                ya < other.yb) return true;
        }
    }
    else return false;
}

// === Collision Detection ===
bool Hitbox::check_collision(Hitbox& other) const {
    if (other.allows_collisions()) {
        if (xb > other.xa &&    // inside left
            xa < other.xb &&    // inside right
            yb > other.ya &&    // inside top
            ya < other.yb) {    // inside bottom
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}
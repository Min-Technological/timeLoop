#include "Collisions.h"

bool Collisions::check_x_collision(Hitbox& other) const {
    /*
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
    */
}

bool Collisions::check_y_collision(Hitbox& other) const {
    /*
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
    */
}

// === Collision Detection ===
bool Collisions::check_collision(Hitbox& other) const {
    /*
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
    */
}
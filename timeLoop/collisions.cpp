#include "Collisions.h"

Collisions::Collisions() {}

bool Collisions::collide_character_chunk(Character* user, Hitbox* chunkHitbox) {
    std::array<float, 2> userVelocity = user->get_velocity();
    if (y_collision(user, chunkHitbox, userVelocity[1]) || x_collision(user, chunkHitbox, userVelocity[0])) {
        return true;
    }
    else {
        return false;
    }
}

void Collisions::collide_character_tile(Character* user, Tile* tile) {
    Hitbox* tileHitbox = tile->get_hitbox();
    std::array<float, 2> userVelocity= user->get_velocity();

    if (!tileHitbox->allows_collisions()) return;

    if (y_collision_solid(user, tileHitbox, userVelocity[0], userVelocity[1])) {
        character_y_solid(user, tileHitbox, userVelocity[1]);
    }
    if (x_collision(user, tileHitbox, userVelocity[0])) {
        character_x_solid(user, tileHitbox, userVelocity[0]);
    }

}

bool Collisions::collide_character_card(Character* user, TarotCard* card)
{

    std::array<float, 2> userVelocity = user->get_velocity();
    if (y_collision(user, card->get_hitbox(), userVelocity[1]) || x_collision(user, card->get_hitbox(), userVelocity[0])) {
        return true;
    }
    else {
        return false;
    }
}



void Collisions::character_x_solid(Character* user, Hitbox* secondary, float xVelocity) {
    Hitbox* primary = user->get_hitbox();
    std::array<float, 4> userPos = primary->get_current_pos();
    std::array<float, 4> otherPos = secondary->get_current_pos();

    if (xVelocity > 0) { // Moving Right
        primary->change_current(
            otherPos[0] - user->w - 0.0001f, // left edge of tile - width
            userPos[1],                     // keep Y the same
            user->w,
            user->h
        );
        user->hit_right();
    }
    else if (xVelocity < 0) { // Moving Left
        primary->change_current(
            otherPos[2] + 0.0001f, // right edge of tile + tiny offset
            userPos[1],            // keep Y the same
            user->w,
            user->h
        );
        user->hit_left();
    }

}

void Collisions::character_y_solid(Character* user, Hitbox* secondary, float yVelocity) {

    Hitbox* primary = user->get_hitbox();
    std::array<float, 4> userPos = primary->get_current_pos();
    std::array<float, 4> otherPos = secondary->get_current_pos();

    if (yVelocity > 0) {

        primary->change_current(
            userPos[0],                     // keep X the same
            otherPos[1] - user->h - 0.0001f, // Top edge - height - tiny offset
            user->w,
            user->h
        );
        user->landed();
    }
    else if (yVelocity < 0) {

        primary->change_current(
            userPos[0],             // keep X the same
            otherPos[3] + 0.0001f,   // Bottom edge + tiny offset
            user->w,
            user->h
        );
        user->hit_head();
    }
}



bool Collisions::x_collision(Character* user, Hitbox* other, float xVelocity)
{

    std::array<float, 4> userPos = user->get_hitbox()->get_current_pos();
    std::array<float, 4> userPre = user->get_hitbox()->get_previous_pos();
    std::array<float, 4> otherPos = other->get_current_pos();
    int xa = 0;
    int ya = 1;
    int xb = 2;
    int yb = 3;

    // Require horizontal overlap
    bool yOverlap = (userPos[yb] > otherPos[ya] && userPos[ya] < otherPos[yb]);
    if (!yOverlap) return false;

    bool xTunnel = false;


    if (xVelocity > 0) {    // Moving Right
        xTunnel = (
            userPos[xb] > otherPos[xa] &&   // inside left
            userPre[xb] < otherPos[xb]       // inside bottom
            );

    }
    else if (xVelocity < 0) {    // Moving Left
        xTunnel = (
            userPre[xa] > otherPos[xa] &&   // inside left
            userPos[xa] < otherPos[xb]       // inside bottom
            );

    }
    else {
        xTunnel = (
            userPos[xb] > otherPos[xa] &&   // inside left
            userPos[xa] < otherPos[xb]      // inside bottom
            );

    }

    return xTunnel;
}

bool Collisions::y_collision(Character* user, Hitbox* other, float yVelocity)
{

    std::array<float, 4> userPos = user->get_hitbox()->get_current_pos();
    std::array<float, 4> userPre = user->get_hitbox()->get_previous_pos();
    std::array<float, 4> otherPos = other->get_current_pos();
    int xa = 0;
    int ya = 1;
    int xb = 2;
    int yb = 3;

    // Require horizontal overlap
    bool otherOverlap = (userPos[xb] > otherPos[xa] && userPos[xa] < otherPos[xb]);
    if (!otherOverlap) return false;

    bool yTunnel = false;

    if (yVelocity > 0) {    // Moving Down
        yTunnel = (
            userPos[yb] > otherPos[ya] &&   // inside top
            userPre[yb] < otherPos[yb]      // inside bottom
            );

    }
    else if (yVelocity < 0) {    // Moving Up
        yTunnel = (
            userPre[ya] > otherPos[ya] &&   // inside top
            userPos[ya] < otherPos[yb]      // inside bottom
            );

    }
    else {
        yTunnel = (
            userPos[yb] > otherPos[ya] &&   // inside top
            userPos[ya] < otherPos[yb]      // inside bottom
            );

    }

    return yTunnel;
}

bool Collisions::y_collision_solid(Character* user, Hitbox* other, float xVelocity, float yVelocity)
{

    std::array<float, 4> userPos = user->get_hitbox()->get_current_pos();
    std::array<float, 4> userPre = user->get_hitbox()->get_previous_pos();
    std::array<float, 4> otherPos = other->get_current_pos();
    int xa = 0;
    int ya = 1;
    int xb = 2;
    int yb = 3;

    // Require horizontal overlap
    bool otherOverlap = (userPos[xb] > otherPos[xa] && userPos[xa] < otherPos[xb]);
    if (!otherOverlap) return false;

    bool yTunnel = false;

    if (yVelocity > 0) {    // Moving Down
        yTunnel = (
            userPos[yb] > otherPos[ya] &&   // inside top
            userPre[yb] < otherPos[yb]      // inside bottom
            );

    }
    else if (yVelocity < 0) {    // Moving Up
        if (
            userPre[ya] > otherPos[ya] &&   // inside top
            userPos[ya] < otherPos[yb]      // inside bottom
            ) {
            float maxOverlap = 16;
            float xOverlap = 0;

            if (xVelocity > 0) {
                xOverlap = userPos[xb] - otherPos[xa];
            }
            else if (xVelocity < 0) {
                xOverlap = otherPos[xb] - userPos[xa];

            }

            yTunnel = (xOverlap > maxOverlap);

        }

    }
    else {
        yTunnel = (
            userPos[yb] > otherPos[ya] &&   // inside top
            userPos[ya] < otherPos[yb]      // inside bottom
            );

    }

    return yTunnel;
}

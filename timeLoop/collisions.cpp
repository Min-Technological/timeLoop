#include "Collisions.h"

Collisions::Collisions() {}

bool Collisions::collide_character_chunk(Character* user, Hitbox* chunkHitbox) {
    std::array<float, 2> userVelocity = user->get_velocity();
    if (y_collision(user->get_hitbox(), chunkHitbox, userVelocity[1]) || x_collision(user->get_hitbox(), chunkHitbox, userVelocity[0])) {
        return true;
    }
    else {
        return false;
    }
}

void Collisions::collide_character_tile(Character* user, Tile* tile) {
    Hitbox* tileHitbox = tile->get_hitbox();
    std::array<float, 2> userVelocity= user->get_velocity();

    if (!tileHitbox->allows_collisions() || !user->get_hitbox()->allows_collisions()) return;

    if (y_collision_solid(user->get_hitbox(), tileHitbox, userVelocity[0], userVelocity[1])) {
        character_y_solid(user, tileHitbox, userVelocity[1]);
    }
    if (x_collision(user->get_hitbox(), tileHitbox, userVelocity[0])) {
        character_x_solid(user, tileHitbox, userVelocity[0]);
    }

}

bool Collisions::collide_character_card(Character* user, TarotCard* card)
{

    if (!card->get_hitbox()->allows_collisions() || !user->get_hitbox()->allows_collisions()) return false;

    std::array<float, 2> userVelocity = user->get_velocity();
    if (y_collision(user->get_hitbox(), card->get_hitbox(), userVelocity[1]) || x_collision(user->get_hitbox(), card->get_hitbox(), userVelocity[0])) {
        return true;
    }
    else {
        return false;
    }
}


void Collisions::collide_enemy_attack(Enemy* enemy, Attack* attack) {

    if (!enemy->get_hitbox()->allows_collisions() || !attack->get_attack()->allows_collisions()) return;

    if (x_collision(enemy->get_hitbox(), attack->get_attack(), 0)) {
        enemy->take_damage(attack->get_damage());
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



bool Collisions::x_collision(Hitbox* main, Hitbox* other, float xVelocity)
{

    std::array<float, 4> mainPos = main->get_current_pos();
    std::array<float, 4> mainPre = main->get_previous_pos();
    std::array<float, 4> otherPos = other->get_current_pos();
    int xa = 0;
    int ya = 1;
    int xb = 2;
    int yb = 3;

    // Require horizontal overlap
    bool yOverlap = (mainPos[yb] > otherPos[ya] && mainPos[ya] < otherPos[yb]);
    if (!yOverlap) return false;

    bool xTunnel = false;


    if (xVelocity > 0) {    // Moving Right
        xTunnel = (
            mainPos[xb] > otherPos[xa] &&   // inside left
            mainPre[xb] < otherPos[xb]       // inside bottom
            );

    }
    else if (xVelocity < 0) {    // Moving Left
        xTunnel = (
            mainPre[xa] > otherPos[xa] &&   // inside left
            mainPos[xa] < otherPos[xb]       // inside bottom
            );

    }
    else {
        xTunnel = (
            mainPos[xb] > otherPos[xa] &&   // inside left
            mainPos[xa] < otherPos[xb]      // inside bottom
            );

    }

    return xTunnel;
}

bool Collisions::y_collision(Hitbox* main, Hitbox* other, float yVelocity)
{

    std::array<float, 4> mainPos = main->get_current_pos();
    std::array<float, 4> mainPre = main->get_previous_pos();
    std::array<float, 4> otherPos = other->get_current_pos();
    int xa = 0;
    int ya = 1;
    int xb = 2;
    int yb = 3;

    // Require horizontal overlap
    bool otherOverlap = (mainPos[xb] > otherPos[xa] && mainPos[xa] < otherPos[xb]);
    if (!otherOverlap) return false;

    bool yTunnel = false;

    if (yVelocity > 0) {    // Moving Down
        yTunnel = (
            mainPos[yb] > otherPos[ya] &&   // inside top
            mainPre[yb] < otherPos[yb]      // inside bottom
            );

    }
    else if (yVelocity < 0) {    // Moving Up
        yTunnel = (
            mainPre[ya] > otherPos[ya] &&   // inside top
            mainPos[ya] < otherPos[yb]      // inside bottom
            );

    }
    else {
        yTunnel = (
            mainPos[yb] > otherPos[ya] &&   // inside top
            mainPos[ya] < otherPos[yb]      // inside bottom
            );

    }

    return yTunnel;
}

bool Collisions::y_collision_solid(Hitbox* main, Hitbox* other, float xVelocity, float yVelocity)
{
    std::array<float, 4> mainPos = main->get_current_pos();
    std::array<float, 4> mainPre = main->get_previous_pos();
    std::array<float, 4> otherPos = other->get_current_pos();
    int xa = 0;
    int ya = 1;
    int xb = 2;
    int yb = 3;

    // Require horizontal overlap
    bool otherOverlap = (mainPos[xb] > otherPos[xa] && mainPos[xa] < otherPos[xb]);
    if (!otherOverlap) return false;

    bool yTunnel = false;

    if (yVelocity > 0) {    // Moving Down
        yTunnel = (
            mainPos[yb] > otherPos[ya] &&   // inside top
            mainPre[yb] < otherPos[yb]      // inside bottom
            );

    }
    else if (yVelocity < 0) {    // Moving Up
        if (
            mainPre[ya] > otherPos[ya] &&   // inside top
            mainPos[ya] < otherPos[yb]      // inside bottom
            ) {
            float maxOverlap = 16;
            float xOverlap = 0;

            if (xVelocity > 0) {
                xOverlap = mainPos[xb] - otherPos[xa];
            }
            else if (xVelocity < 0) {
                xOverlap = otherPos[xb] - mainPos[xa];

            }

            yTunnel = (xOverlap > maxOverlap);

        }

    }
    else {
        yTunnel = (
            mainPos[yb] > otherPos[ya] &&   // inside top
            mainPos[ya] < otherPos[yb]      // inside bottom
            );

    }

    return yTunnel;
}

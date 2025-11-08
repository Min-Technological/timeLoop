#pragma once
#ifndef COLLISIONS
#define COLLISIONS

#include <iostream>
#include "Hitbox.h"
#include "Character.h"
#include "Tile.h"
#include "TarotCard.h"

class Collisions {
public:

    Collisions();

    bool collide_character_chunk(Character* user, Hitbox* chunkHitbox);
    void collide_character_tile(Character* user, Tile* tile);
    bool collide_character_card(Character* user, TarotCard* card);
	 
private:

    void character_x_solid(Character* user, Hitbox* secondary, float xVelocity);
    void character_y_solid(Character* user, Hitbox* secondary, float yVelocity);

    bool x_collision(Character* user, Hitbox* other, float xVelocity);
    bool y_collision(Character* user, Hitbox* other, float yVelocity);
    bool y_collision_solid(Character* user, Hitbox* other, float xVelocity, float yVelocity);

};

#endif

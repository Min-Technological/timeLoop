#pragma once
#ifndef COLLISIONS
#define COLLISIONS

#include <iostream>
#include "Hitbox.h"
#include "Character.h"
#include "Tile.h"
#include "TarotCard.h"
#include "Attack.h"
#include "Enemy.h"

class Collisions {
public:

    Collisions();

    bool collide_character_chunk(Character* user, Hitbox* chunkHitbox);
    void collide_character_tile(Character* user, Tile* tile);
    bool collide_character_card(Character* user, TarotCard* card);
    bool collide_character_enemy(Character* user, Enemy* enemy);

    void collide_enemy_attack(Enemy* enemy, Attack* attack);
	 
private:
    // === Character Interactions ===
    void character_x_solid(Character* user, Hitbox* secondary, float xVelocity);
    void character_y_solid(Character* user, Hitbox* secondary, float yVelocity);
    
    // === Basic Interactions ===
    bool x_collision(Hitbox* main, Hitbox* other, float xVelocity);
    bool y_collision(Hitbox* main, Hitbox* other, float yVelocity);
    bool y_collision_solid(Hitbox* main, Hitbox* other, float xVelocity, float yVelocity);

};

#endif

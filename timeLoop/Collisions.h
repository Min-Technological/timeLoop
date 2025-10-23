#pragma once
#ifndef COLLISIONS
#define COLLISIONS

#include <iostream>
#include "Hitbox.h"
#include "Tile.h"
#include "TarotCard.h"

class Collisions {
public:
	enum CollisionType {
		SOLID,
		PICKUP,
		TOTAL // TOTAL NUMBER, NOT TO BE USED
	};

	// === Assuming the user collides with an external ===;
	CollisionType collide_with_tiles(Hitbox& hitbox1, std::vector<Tile*>* tiles);
	CollisionType collide_with_tarot(Hitbox& hitbox1, Hitbox& hitbox2, TarotCard::CardNumber cardNumber);
	 
private:
	void solid_y_collision(Tile* tile) {

	}
};

#endif

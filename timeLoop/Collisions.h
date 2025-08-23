#pragma once
#ifndef COLLISIONS
#define COLLISIONS

#include <iostream>
#include "Hitbox.h"
#include "Tile.h"

class Collisions {
public:
	enum CollisionType {
		SOLID,
		PICKUP,
		TOTAL // TOTAL NUMBER, NOT TO BE USED
	};

	// === Assuming the user collides with an external ===;
	CollisionType collide_with_tile(Hitbox hitbox1, Hitbox hitbox2, int tileType) {

	}

private:

};

#endif

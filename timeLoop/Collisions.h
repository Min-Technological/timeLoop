#pragma once
#ifndef COLLISIONS
#define COLLISIONS

#include <iostream>
#include "Hitbox.h"
#include "Tile.h"
#include "TarotCard.h"

class Collisions {
public:

    bool check_x_collision(Hitbox& other) const;
    bool check_y_collision(Hitbox& other) const;
    bool check_collision(Hitbox& other) const;
	 
private:

};

#endif

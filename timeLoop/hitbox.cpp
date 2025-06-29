#include "Hitbox.h"

Hitbox::Hitbox() :
xa(0), xb(20), ya(0), yb(40) {}

Hitbox::Hitbox(float x, float y, float width, float height) :
	xa(x), ya(y) {
	xb = x + width; // Right Edge
	yb = y + height; // Bottom Edge
}



void Hitbox::check_collision(Hitbox other) const {
	if (xb > other.xa &&	// inside left
		xa < other.xb &&	// inside right
		yb > other.ya &&	// inside top
		ya < other.yb) {	// inside bottom
		std::cout << "COLLIDING\n";
	}
}
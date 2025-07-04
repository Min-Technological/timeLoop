#include "Hitbox.h"

Hitbox::Hitbox() :
xa(0), xb(20), ya(0), yb(40), w(1920), h(1080) {}

Hitbox::Hitbox(float x, float y, float width, float height) :
	xa(x), ya(y), w(width), h(height) {
	xb = x + width; // Right Edge
	yb = y + height; // Bottom Edge

	bounding = { x, y, width, height };
}

void Hitbox::update_hitbox(float x, float y, float width, float height) {
	xa = x;
	xb = x + width;
	ya = y;
	yb = y + height;
}

void Hitbox::enable_collisions(bool status) {
	allowsCollisions = status;
}

bool Hitbox::allows_collisions() {
	return allowsCollisions;
}



bool Hitbox::check_collision(Hitbox other) const {
	if (other.allows_collisions()) {
		if (xb > other.xa &&	// inside left
			xa < other.xb &&	// inside right
			yb > other.ya &&	// inside top
			ya < other.yb) {	// inside bottom
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

void Hitbox::render_hitbox(SDL_Renderer* r, float xOffset, float scale, int green) {
	bounding.x = (xa - xOffset) * scale;
	bounding.y = ya;
	bounding.w = w * scale;
	bounding.h = h;

	SDL_SetRenderDrawColor(r, 255, green, 0, 255);
	SDL_RenderRect(r, &bounding);
}

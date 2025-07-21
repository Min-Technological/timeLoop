#include "Animations.h"

Animations::Animations(SDL_Texture* texture) :
	t(texture) {}

void Animations::load_sprites(float y, float w, float h, int count) {
	frameCount = count;

	for (int i = 0; i < count; i++) {
		SDL_FRect nextSprite = { (w * i), y, w, h };
		spriteRegions.push_back(nextSprite);
	}
}

SDL_FRect& Animations::get_sprite(int frame) {
	if (frame < frameCount && frame >= 0) {
		return spriteRegions[frame];
	}
	else {
		std::cout << "An error occured returning the sprite!\n";
		return spriteRegions[0];
	}
}

int Animations::get_total_frames() const {
	return frameCount;
}

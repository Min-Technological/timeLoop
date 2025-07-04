#include "Chunk.h"

Chunk::Chunk(float leftEdge, AppWindow window) :
	hitbox(leftEdge, 0, 640, 1080),
	r(window.get_renderer())
{}

void Chunk::append(Tile::TileType type, float x, float y, AppWindow appWindow) {
	chunk.emplace_back(type, x, y, appWindow);
}

void Chunk::update(float viewScale, float xOffset) {
	scale = viewScale;
	xOff = xOffset;

	for (Tile& tile : chunk) {
		tile.update(viewScale, xOffset);
	}
}

void Chunk::render(std::vector<float> screenDimensions) {

	if ((hitbox.xb - xOff) * scale >= 00 &&
		(hitbox.xa - xOff) * scale < screenDimensions[0]) {
		for (Tile& tile : chunk) {
			tile.render(screenDimensions);
		}
	}

	if (showBounding) {
		hitbox.render_hitbox(r, xOff, scale, debug);
	}
}

void Chunk::set_debug(char a) {
	switch (a) {
	case 'G':
		debug = 255;
		break;
	default:
		debug = 0;
		break;
	}
}

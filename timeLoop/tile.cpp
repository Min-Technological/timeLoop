#include "Tile.h"

Tile::Tile(TileType tileType, float xPos, float yPos, AppWindow window, Camera &windowCamera) :
 x(xPos), y(yPos), type(tileType), r(window.get_renderer()), hitbox(xPos, yPos, w, w), camera(windowCamera) {

	fullscreenScale = SDL_GetWindowDisplayScale(window.get_window());
	set_texture();

}

void Tile::handle_event(bool fullscreen) {

}

void Tile::update(float viewScale) {

	renderX = x - camera.xOffset;

	scale = viewScale;
	if (scale != viewScale) {
		std::cout << scale << "\n";
	}

	set_texture();

}

void Tile::render() {
	if (x > -renderW && renderX < camera.w &&
		y > -renderW && renderY < camera.h){
		switch (type) {
		case TileType::DIRT_DARK:
			SDL_SetRenderDrawColor(r, 0xDD, 0x55, 0x00, 0xFF);
			SDL_RenderFillRect(r, &t);
			break;

		case TileType::DIRT_LIGHT:
			SDL_SetRenderDrawColor(r, 0xFF, 0x66, 0x00, 0xFF);
			SDL_RenderFillRect(r, &t);
			break;

		case TileType::GRASS_DARK:
			SDL_SetRenderDrawColor(r, 0x00, 0xDD, 0x00, 0xFF);
			SDL_RenderFillRect(r, &t);
			break;

		case TileType::GRASS_LIGHT:
			SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderFillRect(r, &t);
			break;

		case TileType::NILL:
			SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x0, 0xFF);
			SDL_RenderFillRect(r, &t);
			break;
		}
	}
}

void Tile::set_texture() {

	renderX = renderX * scale;
	renderY = y * scale;
	renderW = w * scale;

	t = { renderX,
		renderY,
		renderW,
		renderW };
}
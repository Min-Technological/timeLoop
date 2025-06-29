#include "Character.h"

Character::Character(float x, float y, float width, float height, AppWindow window) :
	w(width), h(height), newX(x), newY(y), appWindow(window), r(window.get_renderer()) {

	hitbox = std::move(Hitbox(x, y, width, height));
	fullscreenScale = SDL_GetWindowDisplayScale(window.get_window());
	set_texture(0);
}

void Character::handle_event(bool fullscreen) {
}

void Character::move() {
	newX = hitbox.xa;
	newY = hitbox.ya;

	const bool* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_LSHIFT]) {
		sprinting = true;
	}
	else {
		sprinting = false;
	}

	if (keys[SDL_SCANCODE_W]) {
		moveUp(10);
	}

	if (keys[SDL_SCANCODE_A]) {
		moveLeft(10);
	}

	if (keys[SDL_SCANCODE_S]) {
		moveDown(10);
	}

	if (keys[SDL_SCANCODE_D]) {
		moveRight(10);
	}

	if (keys[SDL_SCANCODE_SPACE]) {
		// moveJump();
	}

	if (keys[SDL_SCANCODE_R]) {
		newX = 960;
		newY = 680;
	}

	hitbox = std::move(Hitbox(newX, newY, w, h));

}

void Character::update(float viewScale, float xOffset) {
	scale = viewScale;

	set_texture(xOffset);
}

void Character::render() {
	SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x0, 0xFF);
	SDL_RenderFillRect(r, &t);
}

void Character::moveUp(int px) {
	newY -= sprinting ? px * 2 : px;
}

void Character::moveLeft(int px) {
	newX -= sprinting ? px * 2 : px;
}

void Character::moveDown(int px) {
	newY += sprinting ? px * 2 : px;
}

void Character::moveRight(int px) {
	newX += sprinting ? px * 2 : px;
}

void Character::set_texture(float xOffset) {

	renderX = (newX - xOffset) * scale;
	renderY = newY * scale;
	renderW = w * scale;
	renderH = h * scale;

	t = { renderX,
		renderY,
		renderW,
		renderH };
}

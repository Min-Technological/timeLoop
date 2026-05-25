#include "Titlebar.h"

// === Constructor: load texture ===
Titlebar::Titlebar(int width, int height, std::string buttonTextures, SDL_Renderer* renderer, AppWindow* appWindow)
	: renderer(renderer, 0, 0, 1, 1, dummyValue, dummyValue),
	titleWidth(width),
	titleHeight(height),
	titleBarWindow(appWindow)
{
	this->renderer.load_texture(buttonTextures);
}

// === Handle mouse and keyboard events ===
void Titlebar::handle_event(Input input) {
	if (input.is_key_just_pressed(SDLK_F11)) {
		if (titleBarWindow->is_fullscreen()) {
			titleBarWindow->windowed();
		}
		else {
			titleBarWindow->fullscreen();
		}

		return;
	}

	for (const SDL_Event& e : input.get_events()) {
		if (e.type != SDL_EVENT_MOUSE_MOTION &&
			e.type != SDL_EVENT_MOUSE_BUTTON_DOWN &&
			e.type != SDL_EVENT_MOUSE_BUTTON_UP) {

			continue;

		}

		float x, y;
		SDL_GetMouseState(&x, &y);

		bool withinX = (titleWidth - 3 * buttonWidth) < x && x < titleWidth;
		bool withinY = 0 < y && y < buttonHeight;

		if (!withinX || !withinY) {
			set_state(0, 0, 0);
			isClicking = false;
			continue;
		}

		if (x < titleWidth - 2 * buttonWidth) {
			handle_minimise(e);
		}
		else if (x < titleWidth - buttonWidth) {
			handle_fullscreen(e);
		}
		else {
			handle_close(e);
		}  

		if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
			isClicking = false;
		}
	}
}

// === Button specific handlers ===
void Titlebar::handle_minimise(const SDL_Event &e) {
	if (e.type == (SDL_EVENT_MOUSE_BUTTON_DOWN)) {
		isClicking = true;
		set_state(2, 0, 0);
	}
	else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && isClicking) {
		SDL_MinimizeWindow(titleBarWindow->get_window());
	}
	else if (isClicking) {
		set_state(2, 0, 0);
	}
	else {
		set_state(1, 0, 0);
	}
}

void Titlebar::handle_fullscreen(const SDL_Event& e) {
	if (e.type == (SDL_EVENT_MOUSE_BUTTON_DOWN)) {
		isClicking = true;
		set_state(0, 2, 0);
	}
	else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && isClicking) {
		titleBarWindow->fullscreen();
	}
	else if (isClicking) {
		set_state(0, 2, 0);
	}
	else {
		set_state(0, 1, 0);
	}
}

void Titlebar::handle_close(const SDL_Event& e) {
	if (e.type == (SDL_EVENT_MOUSE_BUTTON_DOWN)) {
		isClicking = true;
		set_state(0, 0, 2);
	}
	else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && isClicking) {
		titleBarWindow->close();
	}
	else if (isClicking) {
		set_state(0, 0, 2);
	}
	else {
		set_state(0, 0, 1);
	}
}

// === Set button sprite states ===
void Titlebar::set_state(int state1, int state2, int state3) {
	states = { state1, state2, state3 };
}

// === Render the titlebar buttons ===
void Titlebar::render() {
	if (!titleBarWindow->is_fullscreen()) {
		renderer.set_render_window(0, 0, 960, 540 + titleHeight);

		for (int i = 0; i < 3; i++) {
			float xPos = titleWidth - buttonWidth * (3 - i);
			renderer.new_position( xPos, 0, buttonWidth, buttonHeight, 0, 0 );
			renderer.render_sprite( buttonWidth * i, buttonHeight * states[i], buttonWidth, buttonHeight);
		}
	}
}

// === Cleanup ===
void Titlebar::destroy() {
	renderer.destroy_texture();
}

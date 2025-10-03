#include "Input.h"

Input::Input() {

}

void Input::handle_event() {
	keys = SDL_GetKeyboardState(NULL);
	events.clear();
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		events.push_back(e);
	}
}

const bool* Input::get_held_keys() {
	return keys;
}

std::vector<SDL_Event> Input::get_events() {
	return events;
}

bool Input::is_key_pressed(SDL_Scancode key) {
	return keys[key];
}

bool Input::is_key_just_pressed(SDL_Keycode key) {
	for (const SDL_Event &e : events) {
		if (e.type != SDL_EVENT_KEY_DOWN) continue;

		if (e.key.key != key) continue;

		return true;
	}

	return false;
}

bool Input::is_event_occurring(SDL_EventType eventType) {
	for (const SDL_Event& e : events) {
		if (e.type != eventType) continue;

		return true;
	}

	return false;
}

bool Input::is_clicking_square(float x, float y, int w, int h) {
	bool clickedSquare = false;
	for (const SDL_Event& e : events) {
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

			float mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			if (mouseY >= y &&
				mouseY <= y + h &&
				mouseX >= x &&
				mouseX <= x + w) {
				clickedSquare = true;
			}

		}
	}
	return clickedSquare;
}

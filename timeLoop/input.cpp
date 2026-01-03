#include "Input.h"

Input::Input(AppWindow* appWindow) :
	window(appWindow)
{
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

		if (e.key.repeat != 0) continue;

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



bool Input::is_clicking_square(float x, float y, float w, float h, float& scale) {

	if (window->is_fullscreen()) {
		titlebarH = 0;
	}
	else {
		titlebarH = TITLEBARH;
	}

	bool clickedSquare = false;
	for (const SDL_Event& e : events) {
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

			float mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			if (mouseY >= y * scale + titlebarH &&
				mouseY <= (y + h) * scale + titlebarH &&
				mouseX >= x * scale &&
				mouseX <= (x + w) * scale) {
				clickedSquare = true;
			}

		}
	}
	return clickedSquare;
}

bool Input::is_clicking_circle(float x, float y, float d) {

	bool clickedCircle = false;
	for (const SDL_Event& e : events) {
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

			float mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			if (
				(mouseX - (x + (d / 2))) * (mouseX - (x + (d / 2))) + 
				(mouseY - (y + (d / 2))) * (mouseY - (y + (d / 2))) <= 
				(d / 2) * (d / 2)
				) {
				clickedCircle = true;
			}

		}
	}
	return clickedCircle;
}

bool Input::is_clicking_ring(float x, float y, float innerD, float outerD) {

	bool clickedRing = false;
	for (const SDL_Event& e : events) {
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

			float mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			float innerR = innerD / 2;
			float outerR = outerD / 2;

			if (
				(mouseX - (x + (outerR))) * (mouseX - (x + (outerR))) +
				(mouseY - (y + (outerR))) * (mouseY - (y + (outerR))) <=
				(outerR) * (outerR)
				&&
				(mouseX - (x + (outerR))) * (mouseX - (x + (outerR))) +
				(mouseY - (y + (outerR))) * (mouseY - (y + (outerR))) >=
				(innerR) * (innerR)
				) {
				clickedRing = true;
			}

		}
	}
	return clickedRing;

}

int Input::get_quadrant(float x, float y, float d, float buffer) {

	float mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	float bufferRadius = buffer / 2;

	if (
		mouseX < x + (d / 2) - bufferRadius && 
		mouseX >= x + bufferRadius
		) {

		if (
			mouseY < y + (d / 2) - bufferRadius && 
			mouseY >= y + bufferRadius
			) {
			return 1;
		}
		else if (
			mouseY > y + (d / 2) + bufferRadius && 
			mouseY <= y + d - bufferRadius
			) {
			return 2;
		}
		else {
			return 0;
		}

	}
	else if (
		mouseX > x + (d / 2) + bufferRadius && 
		mouseX <= x + d - bufferRadius
		) {

		if (
			mouseY < y + (d / 2) - bufferRadius &&
			mouseY >= y + bufferRadius
			) {
			return 3;
		}
		else if (
			mouseY > y + (d / 2) + bufferRadius &&
			mouseY <= y + d - bufferRadius
			) {
			return 4;
		}
		else {
			return 0;
		}

	}
	else {
		return 0;
	}
}

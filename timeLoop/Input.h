#pragma once
#ifndef INPUT
#define INPUT

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>

class Input {
public:
	Input();
	void handle_event();

	const bool* get_held_keys();
	std::vector<SDL_Event> get_events();

	bool is_key_pressed(SDL_Scancode key);
	bool is_key_just_pressed(SDL_Keycode key);
	bool is_event_occurring(SDL_EventType eventType);

private:
	const bool* keys = nullptr;
	std::vector<SDL_Event> events;

};

#endif
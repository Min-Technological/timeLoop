#pragma once
#ifndef INPUT
#define INPUT

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include "Window.h"

class Input {
public:
	Input(AppWindow* window);
	void handle_event();

	const bool* get_held_keys();
	std::vector<SDL_Event> get_events();

	bool is_key_pressed(SDL_Scancode key);
	bool is_key_just_pressed(SDL_Keycode key);
	bool is_event_occurring(SDL_EventType eventType);

	bool is_clicking_square(float x, float y, float w, float h, float& scale);
	bool is_clicking_circle(float x, float y, float d);
	bool is_clicking_ring(float x, float y, float innerR, float outerR);
	int get_quadrant(float x, float y, float d, float buffer);

private:
	const bool* keys = nullptr;
	std::vector<SDL_Event> events;
	AppWindow* window;

	float TITLEBARH = 25.0f;
	float titlebarH = 25.0f;

};

#endif
#pragma once
#ifndef GAMESTATE
#define GAMESTATE

#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <vector>

#include "Window.h"
#include "Titlebar.h"
#include "Time.h"
#include "Background.h"
#include "Character.h"
#include "Camera.h"
#include "Map.h"

class Gamestate {
public:
	bool quit;

	Gamestate();

	void initialise_map();



	// Game Loop Functions
	void set_render_canvas();

	void handle_event();

	void move();

	void update();

	void render();



	// Exit Game Functions
	void close();



	// Game States:
	enum State {
		MENU,
		GAME
	};

	State currentState = State::GAME;
	State get_current_state();
	void change_state();

private:

	void calculate_scale();

	AppWindow window;
	Titlebar titlebar;
	Time time;
	Background background;
	Character user;
	Camera camera;
	Map gameMap0;
	SDL_Event event{};

	std::vector<Tile> currentMap;
	int screenW = 1920;
	int screenH = 1080;
	float scale = 1.0f;
};

#endif

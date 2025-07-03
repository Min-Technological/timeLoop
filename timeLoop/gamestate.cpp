#include "Gamestate.h"
 
Gamestate::Gamestate() :
	window("Test Window", 960, 540, 25),

	titlebar(960, 25, "titleBarIcons.png", window.get_renderer(), &window),

	time(60),

	background(window.get_renderer()),

	user(960, 680, 40, 80, window),

	camera(user, time, screenW, screenH, scale),

	gameMap0("map_test.png", 40, window, camera),

	quit(false) {
	event.type = SDL_EVENT_FIRST;
	std::cout << "INITIALISED!\n";
}

void Gamestate::initialise_map() {
	currentMap = gameMap0.generate_map();
}

void Gamestate::set_render_canvas() {
	SDL_Rect renderWindow;
	if (!(window.is_fullscreen())) {
		renderWindow = { 0, titlebar.titleHeight, 960, 540 };
	}
	else {
		renderWindow = { 0, 0, screenW, screenH };
	}
	SDL_SetRenderViewport(window.get_renderer(), &renderWindow);
}

void Gamestate::handle_event() {

	while (SDL_PollEvent(&event) != 0) {

		if (!window.is_running()) {
			quit = true;
			break;

		}

		// bool fullscreenState = window.is_fullscreen();

		titlebar.handle_event(&event);

		//for (Tile &tile : currentMap) {
		//	tile.handle_event(fullscreenState);
		//}

		//user.handle_event(fullscreenState);
	}

}

void Gamestate::move() {
	user.move();

	user.collide(currentMap);

	camera.affect();
}

void Gamestate::update() {

	calculate_scale();

	background.update(screenW, screenH);

	camera.update();

	user.update(scale, camera.xOffset);

	for (Tile &tile : currentMap) {
		tile.update(scale, camera.xOffset);
	}
}

void Gamestate::render() {
	SDL_SetRenderDrawColor(window.get_renderer(), 0x14, 0x28, 0x20, 0xFF);
	SDL_RenderClear(window.get_renderer());



	titlebar.render();
	set_render_canvas();

	background.render();

	std::vector<float> screenDimensions = { float(camera.w), float(camera.h) };

	for (Tile &tile : currentMap) {
		tile.render(screenDimensions);
	}

	user.render();



	SDL_RenderPresent(window.get_renderer());
	time.sleep_delta();

}

void Gamestate::close() {

	titlebar.destroy();

	window.destroy();

	SDL_Quit();

}

Gamestate::State Gamestate::get_current_state() {
	return currentState;
}

void Gamestate::change_state() {

	const bool* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_ESCAPE]) {
		if (get_current_state() == State::MENU) {
			// currentState = State::GAME;
		}
		else {
			currentState = State::MENU;
		}
	}

}

void Gamestate::calculate_scale() {
	SDL_GetCurrentRenderOutputSize(window.get_renderer(), &screenW, &screenH);
	float windowHeight = window.is_fullscreen() ? float(screenH) : float(screenH) - titlebar.titleHeight;
	scale = float(windowHeight) / 1080;
}

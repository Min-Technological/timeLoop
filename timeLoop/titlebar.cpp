#include "Titlebar.h"

// === Constructor: load texture and initialize button sprite frames ===
Titlebar::Titlebar(int width, int height, std::string buttonTextures, SDL_Renderer* renderer, AppWindow* appWindow)
	: titleWidth(width),
	titleHeight(height),
	titleBarRenderer(renderer),
	titleBarWindow(appWindow),
	titleBarTexture(nullptr),
	isClicking(false),
	minimiseState(0),
	fullscreenState(0),
	closeState(0)
{
	load_texture(buttonTextures);

	load_sprites(minimiseSprites, 0);
	load_sprites(fullscreenSprites, 1);
	load_sprites(closeSprites, 2);
}

// === Load the title bar texture from file ===
void Titlebar::load_texture(std::string texturePath) {
	SDL_Surface* loadedSurface = IMG_Load(texturePath.c_str());
	if (!loadedSurface) {
		std::cout << "UNABLE TO LOAD IMAGE! " << SDL_GetError() << std::endl;
		return;
	}

	titleBarTexture = SDL_CreateTextureFromSurface(titleBarRenderer, loadedSurface);
	if (!titleBarTexture) {
		std::cout << "UNABLE TO CREATE TEXTURE FROM: " << SDL_GetError() << std::endl;
	}

	SDL_DestroySurface(loadedSurface);
}

// === Initialize button sprite rectangles for a column in the sprite sheet ===
void Titlebar::load_sprites(SDL_FRect button[], int column) {
	if (!titleBarTexture) {
		std::cout << "FAILED TO LOAD SPRITE SHEET TEXTURE!\n";
		return;
	}

	float xStart = column * buttonWidth;

	button[0] = { xStart, 0, buttonWidth, buttonHeight };
	button[1] = { xStart, buttonHeight, buttonWidth, buttonHeight };
	button[2] = { xStart, buttonHeight * 2, buttonWidth, buttonHeight };
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
	}
	else {
		for (const SDL_Event& e : input.get_events()) {
			if (e.type == SDL_EVENT_MOUSE_MOTION ||
				e.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
				e.type == SDL_EVENT_MOUSE_BUTTON_UP) {

				float x, y;
				SDL_GetMouseState(&x, &y);

				bool withinX = (titleWidth - 3 * buttonWidth) < x && x < titleWidth;
				bool withinY = 0 < y && y < buttonHeight;

				if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
					isClicking = false;
				}

				if (withinX && withinY) {
					if (x < titleWidth - 2 * buttonWidth) {
						handle_minimise(e);
					}
					else if (x < titleWidth - buttonWidth) {
						handle_fullscreen(e);
					}
					else {
						handle_close(e);
					}
				}
				else {
					if (!isClicking) {
						set_state(0, 0, 0);
					}
				}

			}
		}
	}
}

// === Button specific handlers ===
void Titlebar::handle_minimise(const SDL_Event &e) {
	if (e.type == (SDL_EVENT_MOUSE_BUTTON_DOWN)) {
		isClicking = true;
		set_state(2, 0, 0);
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
		std::cout << "CLOSE\n";
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
	minimiseState = state1;
	fullscreenState = state2;
	closeState = state3;
}

// === Render the titlebar buttons ===
void Titlebar::render() {
	if (!titleBarWindow->is_fullscreen()) {
		renderWindow = { 0, 0, 960, 540 + titleHeight };
		SDL_SetRenderViewport(titleBarRenderer, &renderWindow);

		SDL_FRect renderMinimise = { static_cast<float>(titleWidth - buttonWidth * 3), 0.f, buttonWidth, buttonHeight };
		SDL_FRect renderFullscreen = { static_cast<float>(titleWidth - buttonWidth * 2), 0.f, buttonWidth, buttonHeight };
		SDL_FRect renderClose = { static_cast<float>(titleWidth - buttonWidth), 0.f, buttonWidth, buttonHeight };

		SDL_RenderTexture(titleBarRenderer, titleBarTexture, &minimiseSprites[minimiseState], &renderMinimise);
		SDL_RenderTexture(titleBarRenderer, titleBarTexture, &fullscreenSprites[fullscreenState], &renderFullscreen);
		SDL_RenderTexture(titleBarRenderer, titleBarTexture, &closeSprites[closeState], &renderClose);
	}
}

// === Cleanup ===
void Titlebar::destroy() {
	if (titleBarTexture) {
		SDL_DestroyTexture(titleBarTexture);
		titleBarTexture = nullptr;
	}
}

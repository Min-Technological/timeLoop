#include "Titlebar.h"

Titlebar::Titlebar(int width, int height, std::string buttonTextures, SDL_Renderer* renderer, AppWindow* appWindow)
	: titleWidth(width),
	titleHeight(height),
	titleBarRenderer(renderer),
	titleBarWindow(appWindow)
{
	load_texture(buttonTextures);

	load_sprites(minimiseSprites, 0);
	load_sprites(fullscreenSprites, 1);
	load_sprites(closeSprites, 2);
}


void Titlebar::load_texture(std::string texturePath) {
	// The Final Texture
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(texturePath.c_str());
	if (loadedSurface == NULL) {
		std::cout << "UNABLE TO LOAD IMAGE! " << SDL_GetError() << std::endl;
	}
	else {
		// Create Texture From Surface Pixels
		newTexture = SDL_CreateTextureFromSurface(titleBarRenderer, loadedSurface);
		if (newTexture == NULL) {
			std::cout << "UNABLE TO CREATE TEXTURE FROM: " << SDL_GetError() << std::endl;
		}
		// Get Rid of Old Loaded Surface
		SDL_DestroySurface(loadedSurface);
	}

	titleBarTexture = newTexture;
}

void Titlebar::load_sprites(SDL_FRect button[], int column) {
	if (titleBarTexture == NULL) {
		std::cout << "FAILED TO LOAD SPRITE SHEET TEXTURE!\n";
	}
	else {
		float set = column * buttonWidth;

		button[0].x = set;
		button[0].y = 0;
		button[0].w = buttonWidth;
		button[0].h = buttonHeight;

		button[1].x = set;
		button[1].y = buttonHeight;
		button[1].w = buttonWidth;
		button[1].h = buttonHeight;

		button[2].x = set;
		button[2].y = buttonHeight * 2;
		button[2].w = buttonWidth;
		button[2].h = buttonHeight;
	}

}

void Titlebar::handle_event(SDL_Event* e) {
	if (e->type == SDL_EVENT_MOUSE_MOTION
		|| e->type == SDL_EVENT_MOUSE_BUTTON_DOWN
		|| e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
		//Get mouse position
		float x, y;
		SDL_GetMouseState(&x, &y);
		bool withinX = titleWidth - (3 * buttonWidth) < x && x < titleWidth;
		bool withinY = 0 < y && y < buttonHeight;

		if (e->type == SDL_EVENT_MOUSE_BUTTON_UP) {
			isClicking = false;
		}

		if (withinX && withinY) {

			if (x < titleWidth - (2 * buttonWidth)) {
				handle_minimise(e);
			}
			else if (x < titleWidth - buttonWidth) {
				handle_fullscreen(e);
			}
			else if (x < titleWidth) {
				handle_close(e);
			}
		}
		else {
			if (!isClicking) {
				set_state(0, 0, 0);
			}
		}
	}
	else if (e->type == SDL_EVENT_KEY_DOWN) {
		switch (e->key.key) {
		case SDLK_F11:
			if (titleBarWindow->is_fullscreen()) {
				titleBarWindow->windowed();
			}
			else {
				titleBarWindow->fullscreen();
			}
			break;
		default:
			break;
		}
	}
}

void Titlebar::handle_minimise(SDL_Event* e) {
	if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
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

void Titlebar::handle_fullscreen(SDL_Event* e) {
	if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
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

void Titlebar::handle_close(SDL_Event* e) {
	if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		isClicking = true;
		set_state(0, 0, 2);
		titleBarWindow->close();
	}
	else if (isClicking) {
		set_state(0, 0, 2);
	}
	else {
		set_state(0, 0, 1);
	}
}

void Titlebar::set_state(int state1, int state2, int state3) {
	minimiseState = state1;
	fullscreenState = state2;
	closeState = state3;
}

void Titlebar::render() {

	if (titleBarWindow->is_fullscreen() == false) {
		renderWindow = { 0, 0, 960, 540 + titleHeight };
		SDL_SetRenderViewport(titleBarRenderer, &renderWindow);

		SDL_FRect renderMinimise{};
		renderMinimise.x = titleWidth - buttonWidth * 3;
		renderMinimise.y = 0;
		renderMinimise.w = buttonWidth;
		renderMinimise.h = buttonHeight;

		SDL_FRect renderFullscreen{};
		renderFullscreen.x = titleWidth - buttonWidth * 2;
		renderFullscreen.y = 0;
		renderFullscreen.w = buttonWidth;
		renderFullscreen.h = buttonHeight;

		SDL_FRect renderClose{};
		renderClose.x = titleWidth - buttonWidth;
		renderClose.y = 0;
		renderClose.w = buttonWidth;
		renderClose.h = buttonHeight;

		SDL_RenderTexture(titleBarRenderer, titleBarTexture, &minimiseSprites[minimiseState], &renderMinimise);

		SDL_RenderTexture(titleBarRenderer, titleBarTexture, &fullscreenSprites[fullscreenState], &renderFullscreen);

		SDL_RenderTexture(titleBarRenderer, titleBarTexture, &closeSprites[closeState], &renderClose);
	}
}

void Titlebar::destroy() {
	SDL_DestroyTexture(titleBarTexture);
	titleBarTexture = NULL;
}

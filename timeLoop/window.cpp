#include "Window.h"

AppWindow::AppWindow(std::string title, int width, int height, int titleHeight) :
	windowTitle(title),
	windowWidth(width),
	windowHeight(height + titleHeight),
	windowTitleBar(titleHeight)
{
	create_window(SDL_WINDOW_BORDERLESS);
	create_renderer();
	SDL_SetWindowHitTest(mainWindow, AppWindow::windowHitTest, this);
}

SDL_Window* AppWindow::get_window() {
	return mainWindow;
}

SDL_Renderer* AppWindow::get_renderer() {
	return mainRenderer;
}

SDL_HitTestResult AppWindow::windowHitTest(SDL_Window* win, const SDL_Point* pos, void* data) {
	auto* self = static_cast<AppWindow*>(data);
	if ((pos->y < self->windowTitleBar && pos->x < (self->windowWidth - 3 * 48)) && self->is_fullscreen() == false) {
		return SDL_HITTEST_DRAGGABLE;
	}
	return SDL_HITTEST_NORMAL;
}

void AppWindow::fullscreen() {
	if (!fullScreen) {
		fullScreen = true;
		SDL_SetWindowFullscreen(mainWindow, fullScreen);
	}
}

void AppWindow::windowed() {
	if (fullScreen) {
		fullScreen = false;
		SDL_SetWindowFullscreen(mainWindow, fullScreen);
	}
}

bool AppWindow::is_fullscreen() const {
	return fullScreen;
}

void AppWindow::close() {
	windowRunning = false;
}

bool AppWindow::is_running() const {
	return windowRunning;
}

void AppWindow::create_window(Uint16 windowArgs) {
	// Create Window
	mainWindow = SDL_CreateWindow(windowTitle.c_str(), windowWidth, windowHeight, windowArgs);
	if (mainWindow == NULL) {
		std::cout << "WINDOW COULDN'T BE CREATED! " << SDL_GetError() << std::endl;

	}

}

void AppWindow::create_renderer() {
	// Create Renderer for Window
	mainRenderer = SDL_CreateRenderer(mainWindow, NULL);
	if (mainRenderer == NULL) {
		std::cout << "RENDERER COULD NOT BE CREATED!" << SDL_GetError() << std::endl;
	}
	else {
		// Initialise Renderer Colour
		SDL_SetRenderDrawColor(mainRenderer, 0x14, 0x28, 0x20, 0xFF);
	}
}

void AppWindow::destroy() {
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	SDL_DestroyRenderer(mainRenderer);
	mainRenderer = NULL;
}

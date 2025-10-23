#include "Window.h"

// === Constructor: initialize window and renderer ===
AppWindow::AppWindow(std::string title, int width, int height, int titleHeight) :
	windowTitle(title),
	windowWidth(width),
	windowHeight(height + titleHeight),
	windowTitleBar(titleHeight),
	fullScreen(false),
	windowRunning(true),
	mainWindow(nullptr),
	mainRenderer(nullptr)
{
	create_window(SDL_WINDOW_BORDERLESS);
	create_renderer();
	SDL_SetWindowHitTest(mainWindow, AppWindow::windowHitTest, this);
}

// === Accessors ===
SDL_Window* AppWindow::get_window() {
	return mainWindow;
}

SDL_Renderer* AppWindow::get_renderer() {
	return mainRenderer;
}

// === Window Hit Test for dragging the title bar area ===
SDL_HitTestResult AppWindow::windowHitTest(SDL_Window* win, const SDL_Point* pos, void* data) {
	auto* self = static_cast<AppWindow*>(data);
	if ((pos->y < self->windowTitleBar && pos->x < (self->windowWidth - 3 * 48)) && !self->is_fullscreen()) {
		return SDL_HITTEST_DRAGGABLE;
	}
	return SDL_HITTEST_NORMAL;
}

// === Fullscreen and Windowed modes ===
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

// === Window running state ===
void AppWindow::close() {
	windowRunning = false;
}

bool AppWindow::is_running() const {
	return windowRunning;
}

std::array<float, 2> AppWindow::get_window_dimensions() {
	return {
		static_cast<float>(windowWidth),
		static_cast<float>(windowHeight)
	};
}


// === Private: Create SDL Window ===
void AppWindow::create_window(Uint16 windowArgs) {
	mainWindow = SDL_CreateWindow(windowTitle.c_str(), windowWidth, windowHeight, windowArgs);
	if (mainWindow == nullptr) {
		std::cout << "WINDOW COULDN'T BE CREATED! " << SDL_GetError() << std::endl;
	}
}

// === Private: Create SDL Renderer ===
void AppWindow::create_renderer() {
	mainRenderer = SDL_CreateRenderer(mainWindow, NULL);
	if (mainRenderer == nullptr) {
		std::cout << "RENDERER COULD NOT BE CREATED! " << SDL_GetError() << std::endl;
	}
	else {
		SDL_SetRenderDrawColor(mainRenderer, 0x14, 0x28, 0x20, 0xFF);
	}
}

// === Clean up resources ===
void AppWindow::destroy() {
	if (mainWindow) {
		SDL_DestroyWindow(mainWindow);
		mainWindow = nullptr;
	}

	if (mainRenderer) {
		SDL_DestroyRenderer(mainRenderer);
		mainRenderer = nullptr;
	}
}

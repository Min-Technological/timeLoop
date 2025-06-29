#pragma once
#ifndef WINDOW
#define WINDOW
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

class AppWindow {
public:
	AppWindow(std::string title, int width, int height, int titleHeight);

	SDL_Window* get_window();
	SDL_Renderer* get_renderer();

	static SDL_HitTestResult windowHitTest(SDL_Window* win, const SDL_Point* pos, void* data);

	void fullscreen();
	void windowed();
	bool is_fullscreen() const;

	void close();
	bool is_running() const;

	void destroy();

private:
	std::string windowTitle;
	int windowWidth;
	int windowHeight;
	int windowTitleBar;

	bool fullScreen = false;

	SDL_Window* mainWindow = NULL;
	SDL_Renderer* mainRenderer = NULL;

	bool windowRunning = true;

	void create_window(Uint16 windowArgs);

	void create_renderer();

};




#endif
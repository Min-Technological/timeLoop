#pragma once
#ifndef TAROTREADER
#define TAROTREADER

#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>

class TarotReader {
public:
	TarotReader(AppWindow window, float& s);
	void update();
	void render(bool bounding);

	bool return_scene();
private:
	Renderer renderer;

	bool readerFacing = true;
	void scene_reader();
	void scene_cards();


};

#endif
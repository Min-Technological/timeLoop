#pragma once
#ifndef TAROTREADER
#define TAROTREADER

#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>

class TarotReader {
public:
	TarotReader(AppWindow& w, float& s, float& depth);
	void render(bool bounding);

	void set_reader_state(bool facingReader);

	bool exit_reader(Input& input);
	bool reading_cards(Input& input);

	bool exit_cards(Input& input);

private:
	Renderer renderer;
	AppWindow& window;
	float& renderScale;

	bool readerFacing = true;


};

#endif
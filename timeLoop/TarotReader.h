#pragma once
#ifndef TAROTREADER
#define TAROTREADER

#include "Input.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>

class TarotReader {
public:
	TarotReader(AppWindow& w, float& s);
	void update();
	void rescale();
	void render(bool bounding);

	void set_reader_state(bool facingReader);

	bool exit_reader(Input& input);
	bool reading_cards(Input& input);

	bool exit_cards(Input& input);

	void reading(bool readingTarot);

private:
	Renderer readerRenderer;
	Renderer tarotRenderer;
	AppWindow& window;
	float& renderScale;

	float UIdepth = 1.0f;

	bool readerFacing = true;


};

#endif
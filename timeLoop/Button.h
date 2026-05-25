#pragma once
#ifndef BUTTON
#define BUTTON

#include <iostream>
#include "Renderer.h"
#include "Hitbox.h"
#include "Input.h"
#include "Text.h"
#include <array>
#include <functional>

class Button {
public:
	Button(SDL_Renderer* r, float& scale, float& depth);
	Button(SDL_Renderer* r, float x, float y, float w, float h, float& scale, float& depth);

	void update(Input& input);
	void render();

	void set_on_press(std::function<void()> pressFunction);
	void set_on_hover(std::function<void()> hoverFunction);

	void enable_text(bool state, TTF_Font* font, std::string text, SDL_Color color);


private:

	float& scale;
	Hitbox hitbox;
	Renderer renderer;

	// === Textbox Fields ===
	Text textbox;
	bool textboxActive = false;
	std::string currentText;
	SDL_Color currentColor = { 0x00, 0x00, 0x00, 0xff };
	float textX = 0;
	float textY = 0;

	std::function<void()> onClick;
	std::function<void()> onHover;


};



#endif
#pragma once
#ifndef BUTTON
#define BUTTON

#include <iostream>
#include "Renderer.h"
#include "Hitbox.h"
#include "Input.h"
#include <array>
#include <functional>

class Button {
public:
	Button(SDL_Renderer* r, float& scale, float& depth);
	Button(SDL_Renderer* r, float x, float y, float w, float h, float& scale, float& depth);

	void update(Input& input);
	void render();

	void set_on_press(std::function<void()> pressFunction);


private:

	float& scale;
	Hitbox hitbox;
	Renderer renderer;

	std::function<void()> onClick;


};



#endif
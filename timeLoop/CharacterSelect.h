#pragma once
#ifndef CHARACTERSELECT
#define CHARACTERSELECT

#include "Window.h"
#include "Input.h"
#include "Renderer.h"

class CharacterSelect {
public:
	CharacterSelect(AppWindow* w, float& s);
	void update(Input& input);
	void set_current_selection(int selection);
	int get_selection() const;
	void render();
private:
	AppWindow* window;
	float& windowScale;
	Renderer renderer;

	int selectedCharacter = 0;
};


#endif
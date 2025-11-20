#pragma once
#ifndef CHARACTERSELECT
#define CHARACTERSELECT

#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Enums.h"

class CharacterSelect {
public:
	CharacterSelect(AppWindow* w, float& s);
	void update(Input& input);
	void set_current_selection(Persona selection);
	Persona get_selection() const;
	void render();
private:
	AppWindow* window;
	float& windowScale;

	float UIdepth = 1.0f;
	Renderer renderer;

	Persona selectedCharacter = Persona::PROTAG;
};


#endif
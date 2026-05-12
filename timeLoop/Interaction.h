#pragma once

#include <iostream>
#include <array>
#include "SDL3\SDL.h"
#include "Enums.h"
#include "Text.h"
#include "Input.h"

#ifndef INTERACTION
#define INTERACTION

class Interaction {
public:
	Interaction(SDL_Renderer* r, float& scale, float& depth, Input& input);

	// === NPC Dialogue ===
	void set_text(std::string dialogue);
	void set_gap(float frameDelta); // how many characters per dialogue
	void next_character(CharacterID character);
	void progress_character(CharacterID character);

	void generate_text(Uint64 currentFrame, TTF_Font* font, SDL_Color color);
	void clear();
	void update();
	void render();

	bool interact_input();

private:

	bool rendering = false;
	int frameMax = 10;

	float gapFrame = 1;
	std::string currentText = "DIALOGUE NOT SET!";
	Uint32 startFrame = 0;
	bool newText = true;

	SDL_Texture* currentFace = nullptr;
	SDL_Texture* nextFace = nullptr;

	CharacterID currentCharacter = CharacterID::NILL;
	CharacterID nextCharacter;

	Text text;

	Input& input;

	SDL_Keycode interactionKey = SDLK_E;

	Renderer renderer;

};



#endif
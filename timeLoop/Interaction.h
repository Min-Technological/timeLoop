#pragma once

#include <iostream>
#include "SDL3\SDL.h"
#include "Enums.h"
#include "Text.h"

#ifndef INTERACTION
#define INTERACTION

class Interaction {
public:
	Interaction(SDL_Renderer* r, float& scale, float& depth);

	// === NPC Dialogue ===
	void set_text(std::string dialogue);
	void set_gap(float frameDelta); // how many characters per dialogue
	void next_character(CharacterID character);
	void progress_character(CharacterID character);

	void generate_text(Uint64 currentFrame);

private:
	float gapFrame = 1;
	std::string currentText = "DIALOGUE NOT SET!";
	Uint32 startFrame = 0;
	bool newText = true;

	SDL_Texture* currentFace;
	SDL_Texture* nextFace;

	CharacterID currentCharacter = CharacterID::NILL;
	CharacterID nextCharacter;

	Text text;


};



#endif
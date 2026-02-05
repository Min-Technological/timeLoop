#include "Interaction.h"

Interaction::Interaction(SDL_Renderer* r, float& scale, float& depth) :
	text(r, scale, depth) {}

void Interaction::set_text(std::string dialogue) {
	currentText = dialogue;
}

void Interaction::set_gap(float frameDelta) {
	gapFrame = frameDelta;
}

void Interaction::next_character(CharacterID character) {
	nextCharacter = character;
}

void Interaction::progress_character(CharacterID character) {
	currentCharacter = nextCharacter;
	nextCharacter = character;
}

void Interaction::generate_text(Uint64 currentFrame) {
	text.set_font("AkayaKanadaka_Regular");

	SDL_Color testColor = { 0x00, 0x00, 0x00, 0xFF };

	text.load_text(currentText, testColor);
	text.render_text(0, 0);
	std::cout << "RENDERING TEXT!\n";
}
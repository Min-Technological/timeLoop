#include "Interaction.h"

Interaction::Interaction(SDL_Renderer* r, float& scale, float& depth, Input& input) :
	text(r, scale, depth),
	input(input),
	renderer(r, 0, 0, 1920, 1080, scale, depth) {}

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

void Interaction::generate_text(Uint64 currentFrame, TTF_Font* font, SDL_Color color) {

	if (!interact_input() || rendering) return;

	text.set_font(font);

	text.load_text(currentText, color);

	renderer.destroy_texture();
	renderer.load_texture("dialogue.png");
	
	rendering = true;
}

void Interaction::clear() {
	rendering = false;
}

void Interaction::update() {
	if (!rendering) return;

	std::array<int, 2> textDimension = text.get_dimensions();
	text.new_position(10, 1080 - textDimension[1] - 70, 1000, 200, 0, 0);

	renderer.new_position(0, 0, 1920, 1080, 0, 0);
	renderer.set_alpha(0x80);

}

void Interaction::render() {
	if (rendering) {
		renderer.render_texture();
		text.render_text();
	}
	
}

bool Interaction::interact_input() {

	bool interactionPressed = input.is_key_just_pressed(interactionKey);

	if (interactionPressed) {
		return true;
	}
	else return false;
}


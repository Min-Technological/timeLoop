#include "CharacterSelect.h"

CharacterSelect::CharacterSelect(AppWindow* w, float& s) :
	windowScale(s), 
	window(w),
	renderer(window->get_renderer(), 0, 0, 1920, 1080, s, UIdepth)
{
	renderer.load_texture("charSelectionWheel.png");
}

void CharacterSelect::update(Input& input) {
	// Exit Card Reading Button

	float innerX, innerY, innerD;
	innerX = windowScale * 772;
	innerY = windowScale * 352;
	innerD = windowScale * 375;

	float outerX, outerY, outerD;
	outerX = windowScale * 585;
	outerY = windowScale * 165;
	outerD = windowScale * 750;

	
	if (!window->is_fullscreen()) {
		innerY += 25;
		outerY += 25;
	}

// No Name 0
// Zoe 1
// Amber 2
// Velara 3
// Emma 4
	if (input.is_clicking_circle(innerX, innerY, innerD)) {
		selectedCharacter = Persona::PROTAG;
	}
	else if (input.is_clicking_ring(outerX, outerY, innerD + 40, outerD)) {
		switch (input.get_quadrant(outerX, outerY, outerD, 30 * windowScale)) {
		case 1:
			selectedCharacter = Persona::PENTACLE;
			break;

		case 2:
			selectedCharacter = Persona::CUP;
			break;

		case 3:
			selectedCharacter = Persona::SWORD;
			break;

		case 4:
			selectedCharacter = Persona::WAND;
			break;

		default:
			"NONE CLICKED\n";
			break;
		}
	}
}

void CharacterSelect::set_current_selection(Persona selection) {
	selectedCharacter = selection;
}

Persona CharacterSelect::get_selection() const {
	return selectedCharacter;
}

void CharacterSelect::render() {
	std::array<float, 2> windowDimensions = window->get_window_dimensions();
	float diameter = windowDimensions[1] / 2;
	float radius = diameter / 2;

	std::array<float, 2> topLeft = {
		(windowDimensions[0] / 2) - radius,
		radius
	};

	renderer.new_position(555, 135, 810, 810, 0);
	renderer.render_texture();



}

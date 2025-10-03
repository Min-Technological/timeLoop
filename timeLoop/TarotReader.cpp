#include "TarotReader.h"

TarotReader::TarotReader(AppWindow& w, float& s) :
	renderer(w.get_renderer(), 0, 0, 1920, 1080, s), window(w), renderScale(s) {}



void TarotReader::render(bool bounding) {
	if (bounding) {
		if (readerFacing) {
			renderer.render_clickbox(1463, 83, 342, 603, 0x00);
		}
	}
}



bool TarotReader::exit_reader(Input& input) {
	// Exit Card Reading Button

	float exitX, exitY;
	int exitD;
	exitX = 46 * renderScale;
	exitY = 46 * renderScale;
	exitD = 252 * renderScale;
	if (!window.is_fullscreen()) {
		exitY += 25;
	}
	if (input.is_clicking_circle(exitX, exitY, exitD)) {
		return true;
	}
	else if (input.is_key_just_pressed(SDLK_ESCAPE)) {
		return true;
	}
	else {
		return false;
	}
}

bool TarotReader::reading_cards(Input& input) {

}

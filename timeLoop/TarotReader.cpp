#include "TarotReader.h"

TarotReader::TarotReader(AppWindow& w, float& s, float& depth) :
	renderer(w.get_renderer(), 0, 0, 1920, 1080, s, depth), window(w), renderScale(s) {}



void TarotReader::render(bool bounding) {
	if (bounding) {
		if (readerFacing) {
			renderer.render_clickbox(1463, 83, 342, 603, 0x00);
		}
	}
}

void TarotReader::set_reader_state(bool facingReader) {
	readerFacing = facingReader;
}



bool TarotReader::exit_reader(Input& input) {
	// Exit Card Reading Button

	float exitX, exitY, exitD;
	exitX = renderScale * 46;
	exitY = renderScale * 46;
	exitD = renderScale * 252;
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
	// Card Selection Button
	float stainedWindowX, 
		stainedWindowY, 
		stainedWindowW, 
		stainedWindowH;
	stainedWindowX = 1463 * renderScale;
	stainedWindowY = 83 * renderScale;
	stainedWindowW = 342 * renderScale;
	stainedWindowH = 603 * renderScale;
	if (!window.is_fullscreen()) {
		stainedWindowY += 25;
	}

	if (input.is_clicking_square(stainedWindowX, stainedWindowY, stainedWindowW, stainedWindowH)) {
		return true;
	}
	else {
		return false;
	}
}

bool TarotReader::exit_cards(Input& input) {

	if (input.is_key_just_pressed(SDLK_ESCAPE)) {
		return true;
	}
	else {
		return false;
	}
}

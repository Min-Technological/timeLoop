#include "TarotReader.h"

TarotReader::TarotReader(AppWindow& w, float& s) :
	readerRenderer(w.get_renderer(), 0, 0, 1920, 1080, s, UIdepth), 
	tarotRenderer(w.get_renderer(), 0, 0, 1920, 1080, s, UIdepth),
	window(w), renderScale(s) {}



void TarotReader::update() {
	tarotRenderer.new_position(0, 0, 1920, 1080, 0, 0);
	readerRenderer.new_position(0, 0, 1920, 1080, 0, 0);
}

void TarotReader::rescale() {
	readerRenderer.rescale();
	tarotRenderer.rescale();
	
}

void TarotReader::render(bool bounding) {

	if (readerFacing) {
		readerRenderer.render_texture();
	}
	
	else {
		tarotRenderer.render_texture();
	}

	if (bounding) {
		if (readerFacing) {
			readerRenderer.render_clickbox(1463, 83, 342, 603, 0x00);
		}
		else {
			tarotRenderer.render_clickbox(0, 0, 540, 540, 0xff);
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

void TarotReader::reading(bool readingTarot) {
	if (readingTarot) {
		readerRenderer.destroy_texture();
		tarotRenderer.destroy_texture();

		readerRenderer.load_texture("tarotBasic.png");
		tarotRenderer.load_texture("tarotSelect.png");
	}
	else {
		readerRenderer.destroy_texture();
		tarotRenderer.destroy_texture();
	}
}

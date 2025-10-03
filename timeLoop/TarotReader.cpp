#include "TarotReader.h"

TarotReader::TarotReader(AppWindow window, float& s) :
	renderer(window.get_renderer(), 0, 0, 1920, 1080, s) {}

void TarotReader::update() {

}
void TarotReader::render(bool bounding) {
	if (bounding) {
		if (readerFacing) {
			renderer.render_clickbox(1463, 83, 342, 603, 0x00);
		}
	}
}

bool TarotReader::return_scene() {
	return readerFacing;
}



void TarotReader::scene_reader() {
	readerFacing = true;

}
void TarotReader::scene_cards() {
	readerFacing = false;

}
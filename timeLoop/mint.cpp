#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Gamestate.h"

int main(int argc, char* argsp[]) {

	SDL_Init(NULL);

	Gamestate mint;

	mint.initialise_map();

	while (!mint.quit) {
		mint.handle_event();
		mint.change_state();

		switch (mint.get_current_state()) {
		case (mint.MENU):

			std::cout << "IN DEVELOPMENT!\n";
			break;

		case (mint.GAME):
			
			mint.move(); // handle game movement inputs.

			mint.update(); // update game object collisions.

			mint.render(); // render game to screen.
			break;

		case (mint.PAUSE):
			
			mint.pause_update();

			mint.pause_render();

			break;

		case (mint.SUICIDE):

			mint.suicide_update();

			mint.suicide_render();

			break;

		case (mint.SELECTION):

			mint.selection_update(); // update game object collisions.

			mint.selection_render(); // render selection overlay

			break;

		case (mint.TAROTREADING):
		case (mint.TAROTCARDS):

			mint.tarot_update();

			mint.tarot_render();

			break;

		}
		// mint.print_state();
		mint.increment_frame();
		mint.frameCount++;

	}

	mint.close();

	return 0;

}
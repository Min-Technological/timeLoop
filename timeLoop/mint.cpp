#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Gamestate.h"

int main(int argc, char* argsp[]) {

	SDL_Init(SDL_INIT_AUDIO);

	Gamestate mint;

	mint.initialise_map();



	while (!mint.get_quit()) {
		mint.handle_event();
		mint.change_state();

		switch (mint.get_current_state()) {
		case (State::OPENING):
			mint.intro_update();
			mint.intro_render();

			break;

		case (State::MENU):

			mint.menu_update();
			mint.menu_render();

			break;

		case (State::GAME):
			
			mint.move(); // handle game movement inputs.

			mint.update(); // update game object collisions.

			mint.render(); // render game to screen.

			break;

		case (State::PAUSE):
			
			mint.pause_update();

			mint.pause_render();

			break;

		case (State::SUICIDE):

			mint.suicide_update();

			mint.suicide_render();

			break;

		case (State::SELECTION):

			mint.selection_update(); // update game object collisions.

			mint.selection_render(); // render selection overlay

			break;

		case (State::TAROTREADING):
		case (State::TAROTCARDS):

			mint.tarot_update();

			mint.tarot_render();

			break;

		}
		// mint.print_state();
		mint.increment_frame();

	}

	mint.close();

	return 0;

}
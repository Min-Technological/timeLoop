#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "Gamestate.h"

int main(int argc, char* argsp[]) {

	SDL_Init(NULL);

	Gamestate mint;

	mint.initialise_map();

	while (!mint.quit) {
		
		mint.handle_event(); // handle simple inputs.

		mint.move(); // handle movement inputs.

		mint.update(); // update object collisions.

		mint.render(); // render to screen.

	}

	return 0;

}
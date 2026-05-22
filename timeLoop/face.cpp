#include "Face.h"

Face::Face() {
	update({ tempVertex, tempVertex, tempVertex, tempVertex });
}

void Face::update(std::array<SDL_Vertex, 4> verticies) {
	SDL_Vertex bottomLeft = verticies[0];
	SDL_Vertex bottomRight = verticies[1];
	SDL_Vertex topRight = verticies[2];
	SDL_Vertex topLeft = verticies[3];

	bottomRightTriangle = { bottomLeft, bottomRight, topRight };
	topLeftTriangle = { bottomLeft, topLeft, topRight };
}

void Face::render(Renderer* r) {
	r->render_triangle(topLeftTriangle);
	r->render_triangle(bottomRightTriangle);
}
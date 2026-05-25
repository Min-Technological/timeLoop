#include "Cube.h"

const SDL_FPoint Cube::faceUVs[6][4] = { 
   {  {0.0f, 1.0f}, {1.0f / 6.0f, 1.0f}, {1.0f / 6.0f, 0.0f}, {0.0f, 0.0f} } ,
   {  {1.0f / 6.0f, 1.0f}, {2.0f / 6.0f, 1.0f}, {2.0f / 6.0f, 0.0f}, {1.0f / 6.0f, 0.0f} } ,
   {  {2.0f / 6.0f, 1.0f}, {3.0f / 6.0f, 1.0f}, {3.0f / 6.0f, 0.0f}, {2.0f / 6.0f, 0.0f} } ,
   {  {3.0f / 6.0f, 1.0f}, {4.0f / 6.0f, 1.0f}, {4.0f / 6.0f, 0.0f}, {3.0f / 6.0f, 0.0f} } ,
   {  {4.0f / 6.0f, 1.0f}, {5.0f / 6.0f, 1.0f}, {5.0f / 6.0f, 0.0f}, {4.0f / 6.0f, 0.0f} } ,
   {  {5.0f / 6.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f}, {5.0f / 6.0f, 0.0f} } 
   } ;

Cube::Cube(SDL_Renderer* r, float& scale, float& depth) :
	renderer(r, 0, 0, 1, 1, scale, depth),
	depth(depth),
	faces(),
	scale(scale)
{
	renderer.load_texture("tempCube.png");
}

void Cube::scale_cube(float sideLength) {
	sideScale = sideLength / 2;
}

void Cube::rotate(float angleA, float angleB, float angleC) {

	currentA = angleA;
	targetA = angleA;
	
	currentB = angleB;
	targetB = angleB;

	currentC = angleC;
	targetC = angleC;

}

void Cube::lerp_rotate(float angleA, float angleB, float angleC) {
	targetA = angleA;
	targetB = angleB;
	targetC = angleC;
}

void Cube::update(float xOff, float yOff) {

	lerp_angles();

	angle_a(currentA);
	angle_b(currentB);
	angle_c(currentC);

	calculate_points();

	calculate_uv(xOff, yOff);
	
	calculate_z_depths();
	sort_indexes();
}

void Cube::render_wireframe(float xOff, float yOff) {
	for (int i = 0; i < 4; i++) {
		int next = (i + 1) % 4;


		std::array<float, 2> point1 = points[i];
		std::array<float, 2> point2 = points[next];
		std::array<float, 2> point3 = points[i+4];
		std::array<float, 2> point4 = points[next+4];

		renderer.render_line(point1[0] + xOff, point1[1] + yOff, point2[0] + xOff, point2[1] + yOff);
		renderer.render_line(point3[0] + xOff, point3[1] + yOff, point4[0] + xOff, point4[1] + yOff);
		renderer.render_line(point1[0] + xOff, point1[1] + yOff, point3[0] + xOff, point3[1] + yOff);
	}
}

void Cube::render_textured() {
	for (int index : faceIndexes) {
		faces[index].render(&renderer);
	}
}


void Cube::angle_a(float angleA) {
	for (int i = 0; i < 8; i++) {

		float newX = xCoords[i] * sideScale;
		float newY = yCoords[i] * sideScale;
		float newZ = zCoords[i] * sideScale;

		rotatedX[i] = newX;

		rotatedY[i] = newY * std::cos(angleA) - newZ * std::sin(angleA);

		rotatedZ[i] = newY * std::sin(angleA) + newZ * std::cos(angleA);
	}
}

void Cube::angle_b(float angleB) {

	std::array<float, 8> xCopy = rotatedX;
	std::array<float, 8> yCopy = rotatedY;
	std::array<float, 8> zCopy = rotatedZ;



	for (int i = 0; i < 8; i++) {

		float newX = xCopy[i];
		float newY = yCopy[i];
		float newZ = zCopy[i];

		rotatedX[i] = newX * std::cos(angleB) + newZ * std::sin(angleB);

		rotatedY[i] = newY;

		rotatedZ[i] = newZ * std::cos(angleB) - newX * std::sin(angleB);
	}
}

void Cube::angle_c(float angleC) {

	std::array<float, 8> xCopy = rotatedX;
	std::array<float, 8> yCopy = rotatedY;
	std::array<float, 8> zCopy = rotatedZ;



	for (int i = 0; i < 8; i++) {

		float newX = xCopy[i];
		float newY = yCopy[i];
		float newZ = zCopy[i];

		rotatedX[i] = newX * std::cos(angleC) - newY * std::sin(angleC);

		rotatedY[i] = newX * std::sin(angleC) + newY * std::cos(angleC);

		rotatedZ[i] = newZ;
	}
}

std::array<float, 2> Cube::calculate_point(float x, float y, float z) {
	std::array<float, 2> point = { 0, 0 };
	float newX = x / (1 + (z / depth));
	float newY = y / (1 + (z / depth));

	return { newX, newY };
}

void Cube::calculate_points() {
	for (int i = 0; i < 8; i++) {
		float x = rotatedX[i];
		float y = rotatedY[i];
		float z = rotatedZ[i];

		points[i] = calculate_point(x, y, z);
	}
}

void Cube::calculate_uv(float xOff, float yOff) {

	// Vertex variables for each four corners of each face.
	std::array<SDL_Vertex, 4> v;

	// Face 1
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 4; i++) {
			int j = faceSets[k][i];

			float xPos = points[j][0] + xOff;
			float yPos = points[j][1] + yOff;

			v[i].position = { xPos * scale, yPos * scale };
			v[i].color = { 1.0f, 1.0f, 1.0f, 0.5f };
			v[i].tex_coord = faceUVs[k][i];
		}
		faces[k].update(v);
	}
}

void Cube::calculate_z_depths() {

	for (int i = 0; i < 6; i++) {
		float accumulator = 0.0f;
		for (int index : faceSets[i]) {
			accumulator += rotatedZ[index];
		}
		zDepths[i] = accumulator / 4.0f;
	}
}

void Cube::sort_indexes() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 5 - i; j++) {
			if (zDepths[faceIndexes[j]] < zDepths[faceIndexes[j + 1]]) {
				int temp = faceIndexes[j + 1];
				faceIndexes[j + 1] = faceIndexes[j];
				faceIndexes[j] = temp;
			}
		}
	}
}

void Cube::lerp_angles() {
	currentA += (targetA - currentA) * blendFactor;
	currentB += (targetB - currentB) * blendFactor;
	currentC += (targetC - currentC) * blendFactor;
}


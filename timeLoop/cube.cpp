#include "Cube.h"

Cube::Cube(SDL_Renderer* r, float& s, float& depth) :
	renderer(r, 0, 0, 1, 1, s, depth),
	depth(depth)
{}

void Cube::scale_cube(double sideLength) {
	sideScale = sideLength / 2;
}

void Cube::rotate(double angleA, double angleB, double angleC) {


	std::cout << "UPDATING CUBE! - " << angleA << "\n";

	angle_a(angleA);
	angle_b(angleB);
	angle_c(angleC);

	calculate_points();
}

void Cube::render(float xOff, float yOff) {
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

void Cube::angle_a(double angleA) {
	for (int i = 0; i < 8; i++) {

		double newX = xCoords[i] * sideScale;
		double newY = yCoords[i] * sideScale;
		double newZ = zCoords[i] * sideScale;

		rotatedX[i] = newX;

		rotatedY[i] = newY * std::cos(angleA) - newZ * std::sin(angleA);

		rotatedZ[i] = newY * std::sin(angleA) + newZ * std::cos(angleA);
	}
}

void Cube::angle_b(double angleB) {

	std::array<double, 8> xCopy = rotatedX;
	std::array<double, 8> yCopy = rotatedY;
	std::array<double, 8> zCopy = rotatedZ;



	for (int i = 0; i < 8; i++) {

		double newX = xCopy[i];
		double newY = yCopy[i];
		double newZ = zCopy[i];

		rotatedX[i] = newX * std::cos(angleB) + newZ * std::sin(angleB);

		rotatedY[i] = newY;

		rotatedZ[i] = newZ * std::cos(angleB) - newX * std::sin(angleB);
	}
}

void Cube::angle_c(double angleC) {

	std::array<double, 8> xCopy = rotatedX;
	std::array<double, 8> yCopy = rotatedY;
	std::array<double, 8> zCopy = rotatedZ;



	for (int i = 0; i < 8; i++) {

		double newX = xCopy[i];
		double newY = yCopy[i];
		double newZ = zCopy[i];

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

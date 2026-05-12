#pragma once

#ifndef CUBE
#define CUBE

#include <iostream>
#include <array>
#include <cmath>
#include "Renderer.h"

class Cube {
public:
	Cube(SDL_Renderer* r, float& s, float& depth);

	void scale_cube(double sideLength);
	void rotate(double angleA, double angleB, double angleC);

	void render(float xOff, float yOff);

private:

	std::array<double, 8> xCoords = { -1, 1, 1, -1, -1, 1, 1, -1 };
	std::array<double, 8> yCoords = { -1, -1, 1, 1, -1, -1, 1, 1 };
	std::array<double, 8> zCoords = { -1, -1, -1, -1, 1, 1, 1, 1 };

	std::array<double, 8> rotatedX = xCoords;
	std::array<double, 8> rotatedY = yCoords;
	std::array<double, 8> rotatedZ = zCoords;

	void angle_a(double angleA);
	void angle_b(double angleB);
	void angle_c(double angleC);

	std::array<std::array<float, 2>, 8> points = { { { -1, -1},{-1, 1},{1, 1},{1, -1},{-1, -1},{-1, 1},{1, 1},{1, -1} } };
	std::array<float, 2> calculate_point(float x, float y, float z);
	void calculate_points();

	double sideScale = 1;

	float& depth;

	Renderer renderer;
};


#endif

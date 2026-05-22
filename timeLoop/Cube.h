#pragma once

#ifndef CUBE
#define CUBE

#include <iostream>
#include <array>
#include <cmath>
#include "Face.h"
#include "Renderer.h"

class Cube {
public:
	Cube(SDL_Renderer* r, float& s, float& depth);

	void scale_cube(double sideLength);
	void rotate(double angleA, double angleB, double angleC);
	void update(float xOff, float yOff);

	void render_wireframe(float xOff, float yOff);
	void render_textured();

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
	
	// Wire-Frame rendering
	std::array<float, 2> calculate_point(float x, float y, float z);
	void calculate_points();

	// Texture Rendering
	void calculate_uv(float xOff, float yOff);

	void calculate_z_depths();
	void sort_indexes();

	double sideScale = 1;

	float& depth;

	Renderer renderer;

	// Face Objects
	std::array<Face, 6> faces;

	// Index of face corners as per Points
	static constexpr int faceSets[6][4] = {
		{ 0, 1, 2, 3 },
		{ 5, 4, 7, 6 },
		{ 1, 5, 6, 2 },
		{ 4, 0, 3, 7 },
		{ 3, 2, 6, 7 },
		{ 1, 0, 4, 5 }
	};

	// UVs for each face
	static const SDL_FPoint faceUVs[6][4];

	// Average Z-depth
	float zDepths[6] = { 1, 1, 1, 1, 1, 1 };

	// Face Indexes
	int faceIndexes[6] = { 0, 1, 2, 3, 4, 5 };

};


#endif

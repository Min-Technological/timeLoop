#pragma once
#ifndef CAMERA_DEPTH
#define CAMERA_DEPTH

#include <iostream>

class CameraDepth {
public:
	CameraDepth(float& depth);

	void set_depth(float depthValue);
	float get_depth();

	float scale_value(float value);

private:
	float& depthValue;

	float get_inverse_depth();

};



#endif
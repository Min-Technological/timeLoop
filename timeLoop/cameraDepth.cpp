#include "CameraDepth.h"

CameraDepth::CameraDepth(float& depth) :
	depthValue(depth) {
}

void CameraDepth::set_depth(float depthValue) {
	this->depthValue = depthValue;
}

float CameraDepth::get_depth() {
	return depthValue;
}

float CameraDepth::scale_value(float value) {
	return (value * get_inverse_depth());
}

float CameraDepth::get_inverse_depth() {
	return (1.0f / depthValue);
}
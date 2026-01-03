#include "Button.h"

Button::Button(SDL_Renderer* r, float& scale, float& depth) :
	scale(scale),
	hitbox(0, 0, 1, 1),
	renderer(r, 0, 0, 1, 1, scale, depth)
{}

Button::Button(SDL_Renderer* r, float x, float y, float w, float h, float& scale, float& depth) :
	scale(scale),
	hitbox(x, y, w, h),
	renderer(r, x, y, w, h, scale, depth)
{}

void Button::update(Input& input) {
	std::array<float, 4> position = hitbox.get_previous_pos();

	renderer.new_position(position[0], position[1], (position[2] - position[0]), (position[3] - position[1]), 0, 0);

	if (input.is_clicking_square(position[0], position[1], (position[2] - position[0]), (position[3] - position[1]), scale)) {
		if (onClick) onClick();
	}

}

void Button::render() {
	renderer.render_colour(0xff, 0x00, 0x50, 0xff);

}


void Button::set_on_press(std::function<void()> pressFunction) {
	onClick = pressFunction;
}



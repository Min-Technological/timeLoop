#include "Button.h"

Button::Button(SDL_Renderer* r, float& scale, float& depth) :
	scale(scale),
	hitbox(0, 0, 1, 1),
	renderer(r, 0, 0, 1, 1, scale, depth),
	textbox(r, scale, depth)
{}

Button::Button(SDL_Renderer* r, float x, float y, float w, float h, float& scale, float& depth) :
	scale(scale),
	hitbox(x, y, w, h),
	renderer(r, x, y, w, h, scale, depth),
	textbox(r, scale, depth)
{}

void Button::update(Input& input) {
	std::array<float, 4> position = hitbox.get_previous_pos();

	renderer.new_position(position[0], position[1], (position[2] - position[0]), (position[3] - position[1]), 0, 0);

	if (input.is_mouse_inside(position[0], position[1], (position[2] - position[0]), (position[3] - position[1]), scale)) {
		if (onHover) onHover();
	}

	if (input.is_clicking_square(position[0], position[1], (position[2] - position[0]), (position[3] - position[1]), scale)) {
		if (onClick) onClick();
	}

	if (!textboxActive) return;

	std::array<int,2> textureDimensions = textbox.get_dimensions();
	float textScale = static_cast<float>(textureDimensions[0]) / static_cast<float>(textureDimensions[1]);

	float buttonW = position[2] - position[0];
	float buttonH = position[3] - position[1];

	float textWidth = buttonH * textScale;

	float freeX = buttonW - (buttonH * textScale);
	textX = position[0] + (freeX / 2.0f);

	textbox.new_position(textX, position[1], textWidth, buttonH, 0, 0);

}

void Button::render() {
	renderer.render_colour(0xff, 0x00, 0x50, 0xff);

	if (!textboxActive) return;

	textbox.render_text();

}


void Button::set_on_press(std::function<void()> pressFunction) {
	onClick = pressFunction;
}

void Button::set_on_hover(std::function<void()> hoverFunction) {
	onHover = hoverFunction;
}

void Button::enable_text(bool state, TTF_Font* font, std::string text, SDL_Color color) {
	textboxActive = true;
	currentText = text;
	currentColor = color;

	textbox.set_font(font);
	textbox.load_text(text, color);
}



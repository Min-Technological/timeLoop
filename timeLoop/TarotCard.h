#pragma once
#ifndef TAROTCARD
#define TAROTCARD

#include <iostream>
#include <vector>
#include "Renderer.h"
#include "Window.h"
#include "Hitbox.h"

class TarotCard {
public:
	TarotCard(int cardType, float X, float Y, AppWindow appWindow);
	enum CardNumber {
		FOOL,
		MAGICIAN,
		HIGH_PRIESTESS,
		EMPRESS,
		EMPEROR,
		HIGH_PRIEST,
		LOVERS,
		CHARIOT,
		STRENGTH,
		HERMIT,
		WHEEL_OF_FORTUNE,
		JUSTICE,
		HANGED_MAN,
		DEATH,
		TEMPERANCE,
		DEVIL,
		TOWER,
		STAR,
		MOON,
		SUN,
		JUDGEMENT,
		WORLD,
		TOTAL
	};
	void update(float viewScale, float offset);
	void render(std::vector<float> screenDimensions);

	CardNumber get_card_number() const;
	Hitbox hitbox;

private:
	// === General Information ===
	CardNumber cardNumber;
	std::string name;
	std::string description;

	// === Location Parameters ===
	float x, y;
	float w = 40;
	float h = 80;
	float scale = 1;
	Renderer renderer;

	// === States ===
	bool collected = false;
	bool bounding = true;
};

#endif
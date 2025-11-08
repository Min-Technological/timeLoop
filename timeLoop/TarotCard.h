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
	TarotCard(int cardType, float X, float Y, AppWindow appWindow, float& s);
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
	void update(float offset);
	void render(std::vector<float> screenDimensions);
	void destroy();

	Hitbox* get_hitbox();

	CardNumber get_card_number() const;
	std::string get_card_name() const;

	void collect(bool state);
	bool collected();

	TarotCard(const TarotCard&) = delete;
	TarotCard& operator=(const TarotCard&) = delete;
private:
	// === General Information ===
	CardNumber cardNumber;
	std::string name;
	std::string description;

	// === Location Parameters ===
	float x, y;
	float w = 40; // 40
	float h = 80; // 80
	Hitbox hitbox;
	Renderer renderer;

	// === States ===
	bool cardCollected = false;
	bool bounding = true;
};

#endif
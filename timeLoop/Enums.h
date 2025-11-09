#pragma once
#ifndef PERSONA
#define PERSONA

enum class Persona {
	PROTAG,     // <Unnnamed>
	CUP,        // TEMP NAME <ZOE>
    SWORD,      // TEMP NAME <AMBER>
    WAND,       // TEMP NAME <VELARA>
    PENTACLE    // TEMP NAME <EMMA>

};


enum class State {
    MENU,
    GAME,
    PAUSE,
    SUICIDE,
    REWIND,
    SELECTION,
    TAROTREADING,
    TAROTCARDS,
    TOTAL
};


enum class CardNumber {
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
#endif
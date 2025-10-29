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
#endif
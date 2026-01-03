#pragma once
#ifndef MUSICPLAYER
#define MUSICPLAYER

#include <iostream>
#include <SDL3/SDL.h>

class MusicPlayer {
public:
	MusicPlayer();

	void load_track(std::string title);

	void clear_track();

	void play_track(bool paused);

	void adjust_gain(float gain);


private:

	bool is_playing();

	Uint8* audioBuf = nullptr;
	Uint32 audioLen = 0;

	std::string currentTitle = "null.null";

	SDL_AudioDeviceID deviceID;
	SDL_AudioSpec deviceSpec;

	SDL_AudioStream* currentStream = nullptr;


	bool playing = false;
	float currentGain = -1.0f;

};



#endif

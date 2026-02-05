#pragma once
#ifndef MUSICPLAYER
#define MUSICPLAYER

#include <iostream>
#include <SDL3/SDL.h>

class MusicPlayer {
public:
	MusicPlayer();

	void load_track(std::string title);

	void play_track(bool paused);

	void end_track();

	void adjust_gain(float gain);


private:

	bool is_playing();

	void clear_track();

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

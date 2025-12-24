#include "MusicPlayer.h"

MusicPlayer::MusicPlayer() {
	// temp Values
	SDL_AudioSpec tempSpecs{
		SDL_AUDIO_S16, // 32 Bit Format
		2, // Stereo has 2 channels
		48000 // sample rate
	};

	deviceID = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
	std::cout << "l" << deviceID << "l\n";

	SDL_GetAudioDeviceFormat(deviceID, &deviceSpec, NULL);
	SDL_AudioStream* stream = SDL_CreateAudioStream(
		&tempSpecs,
		&deviceSpec
	);

}

void MusicPlayer::clear_track() {
	SDL_free(audioBuf);
	audioBuf = nullptr;
	audioLen = 0;

	SDL_UnbindAudioStream(currentStream);
	SDL_DestroyAudioStream(currentStream);

}


void MusicPlayer::load_track(std::string title) {

	if (title == currentTitle) return;

	clear_track();

	currentTitle = title;

	// temp Values
	SDL_AudioSpec tempSpecs{
		SDL_AUDIO_S16, // 32 Bit Format
		2, // Stereo has 2 channels
		48000
	};

	currentTitle = title;

	SDL_LoadWAV(title.c_str(), &tempSpecs, &audioBuf, &audioLen);

	currentStream = SDL_CreateAudioStream(&tempSpecs, &deviceSpec);

	// Bind and feed
	SDL_BindAudioStream(deviceID, currentStream);
	SDL_PutAudioStreamData(currentStream, audioBuf, audioLen);

	// Play
	SDL_ResumeAudioDevice(deviceID);

}

void MusicPlayer::play_track() {

}

bool MusicPlayer::is_playing() {
	return false;
}

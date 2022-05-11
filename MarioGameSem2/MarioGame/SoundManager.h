#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>

class SoundManager
{
public:
	SoundManager(SoundManager* sound_manager, std::string filePath, int preferred_channel);
	~SoundManager();

	void PlaySound(int loops = 0);
	void Stop();

	void SetPrefferedChannel(int channel) { this->m_preferred_channel = channel; }
	
	bool isLoaded() { return this->m_sound != nullptr; }

private:
	SoundManager* m_sound_manager;
	Mix_Music* m_sound;
	int m_last_channel;
	int m_preferred_channel;
};


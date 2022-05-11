#include "SoundManager.h"

SoundManager::SoundManager(SoundManager* sound_manager, std::string filePath, int preferred_channel)
{

}

SoundManager::~SoundManager()
{
	Mix_FreeMusic(m_music);
	m_music = nullptr;

	Mix_FreeChunk(m_sound);
	m_sound = nullptr;
}


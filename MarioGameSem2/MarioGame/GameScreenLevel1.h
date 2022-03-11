#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <iostream>
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include "PowBlock.h"

class Character;

class Texture2D;

class PowBlock;

class GameScreenLevel1:GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e);
	void UpdatePowBlock();

private:
	LevelMap* m_level_map;
	Texture2D* m_background_texture;
	Character* character_mario;
	Character* character_luigi;
	PowBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();

	bool SetUpLevel();
	void SetLevelMap();
};

#endif
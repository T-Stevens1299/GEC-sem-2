#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <iostream>
#include <vector>

#include "GameScreen.h"
#include "Commons.h"
#include "Collisions.h"
#include "SoundManager.h"

#include "LevelMap.h"
#include "PowBlock.h"

#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "Coin.h"

class Character;

class Texture2D;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e);

	void UpdatePowBlock();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	

private:
	LevelMap* m_level_map;
	Texture2D* m_background_texture;
	CharacterMario* character_mario;
	CharacterLuigi* character_luigi;
	CharacterKoopa* Koopa;
	PowBlock* m_pow_block;
	Coin* m_Coin;

	SoundManager* m_sound_system;

	std::vector<CharacterKoopa*> m_enemies;
	std::vector<Coin*> m_coins;

	int enemyIndexToDelete;
	int coinIndexToDelete;

	bool MarioDead = false;
	bool LuigiDead = false;
	bool m_screenshake;

	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();

	bool SetUpLevel();
	void SetLevelMap();

	
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoins(Vector2D position);
};

#endif
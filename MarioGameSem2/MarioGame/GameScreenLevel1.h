#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include <iostream>
#include <vector>

#include "GameScreen.h"
#include "Commons.h"
#include "Collisions.h"

#include "LevelMap.h"
#include "PowBlock.h"

#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"

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

	SDL_Rect camera;

private:
	LevelMap* m_level_map;
	Texture2D* m_background_texture;
	CharacterMario* character_mario;
	CharacterLuigi* character_luigi;
	CharacterKoopa* Koopa;
	PowBlock* m_pow_block;

	std::vector<CharacterKoopa*> m_enemies;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	void DoScreenShake();

	bool SetUpLevel();
	void SetLevelMap();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
};

#endif
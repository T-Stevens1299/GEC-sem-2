#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <iostream>
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"

class Character;

class Texture2D;

class GameScreenLevel1:GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* m_background_texture;
	Character* my_character;

	bool SetUpLevel();
};

#endif
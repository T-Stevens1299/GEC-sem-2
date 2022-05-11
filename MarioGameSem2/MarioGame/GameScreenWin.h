#pragma once

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenWin : GameScreen
{
public:
	GameScreenWin(SDL_Renderer* renderer);
	~GameScreenWin();
	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* m_background_texture;

	bool SetUpLevel();
};
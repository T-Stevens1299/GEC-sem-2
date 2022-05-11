#pragma once

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenLose : GameScreen
{
public:
	GameScreenLose(SDL_Renderer* renderer);
	~GameScreenLose();
	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* m_background_texture;

	bool SetUpLevel();
};
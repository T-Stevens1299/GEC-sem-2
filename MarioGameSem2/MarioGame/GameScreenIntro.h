#pragma once

#include <SDL.h>
#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenIntro : GameScreen
{
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();
	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* m_background_texture;

	bool SetUpLevel();
};


#include "GameScreenWin.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "GameScreen.h"

GameScreenWin::GameScreenWin(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenWin::~GameScreenWin()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenWin::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenWin::Update(float deltaTime, SDL_Event e)
{
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			m_screen_to_change = SCREEN_MENU;
			break;
		case SDLK_ESCAPE:
			exit(1);
		default:
			break;
		}
	}
}

bool GameScreenWin::SetUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/WinScreen.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
}
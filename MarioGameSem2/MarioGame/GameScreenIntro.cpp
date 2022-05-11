#include "GameScreenIntro.h"
#include <iostream>
#include "Texture2D.h"
#include "GameScreenManager.h"
#include "GameScreen.h"

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenIntro::~GameScreenIntro() 
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenIntro::Render() 
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) 
		{
		case SDLK_SPACE:
			m_screen_to_change = SCREEN_LEVEL1;
			break;
		default:
			break;
		}
	}
}

bool GameScreenIntro::SetUpLevel() 
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Menu.png")) 
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
}
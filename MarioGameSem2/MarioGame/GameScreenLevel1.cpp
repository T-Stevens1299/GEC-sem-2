#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>
using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1() 
{
	m_background_texture = nullptr;
	my_character = nullptr;
}


void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
	my_character->Update(deltaTime, e);
}

void GameScreenLevel1::Render() 
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	my_character->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if(!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) 
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));
}
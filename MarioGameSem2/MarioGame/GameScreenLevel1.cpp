#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <iostream>
using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1() 
{
	delete(m_background_texture);
	m_background_texture = nullptr;

	delete(character_mario);
	character_mario = nullptr;

	delete(character_luigi);
	character_luigi = nullptr;

	delete(m_level_map);
	m_level_map = nullptr;

	delete(m_pow_block);
	m_pow_block = nullptr;
}


void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{

	if (m_screenshake) 
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		if (m_shake_time <= 0.0f) 
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	character_mario->Update(deltaTime, e);
	character_luigi->Update(deltaTime, e);

	UpdatePowBlock();

	if (Collisions::Instance()->Box(character_mario->GetCollisionBox(), character_luigi->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

	if (Collisions::Instance()->Circle(character_mario, character_luigi))
	{
		cout << "Circle hit!" << endl;
	}
}

void GameScreenLevel1::Render() 
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	character_mario->Render();
	character_luigi->Render();
	m_pow_block->Render();
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}

bool GameScreenLevel1::SetUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture!" << endl;
		return false;
	}

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	character_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	character_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);
}

void GameScreenLevel1::SetLevelMap() 
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									   { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::UpdatePowBlock() 
{
	if (Collisions::Instance()->Box(character_mario->GetCollisionBox(), m_pow_block->GetCollisionBox())) 
	{
		if (m_pow_block->isAvailable()) 
		{
			if (character_mario->isJumping()) 
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				character_mario->CancelJump();
			}
		}
	}
	if (Collisions::Instance()->Box(character_luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->isAvailable())
		{
			if (character_luigi->isJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				character_luigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenShake() 
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}
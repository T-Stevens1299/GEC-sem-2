#include "GameScreenLevel1.h"

#include "Character.h"

#include "Texture2D.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	enemyIndexToDelete = -1;
	coinIndexToDelete = -1;
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

	m_enemies.clear();
	m_coins.clear();
}


void GameScreenLevel1::Update(float deltaTime, SDL_Event e) 
{
	//camera.x = (SCREEN_WIDTH / 2);

	//if (camera.x < 0)
	//{
	//	camera.x = 0;
	//}

	//if (camera.x > LEVEL_WIDTH - camera.w) 
	//{
	//	camera.x = (LEVEL_WIDTH - camera.w);
	//}

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

	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);

	if (Collisions::Instance()->Box(character_mario->GetCollisionBox(), character_luigi->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

	if (Collisions::Instance()->Circle(character_mario, character_luigi))
	{
		cout << "Circle hit!" << endl;
	}

	//if (character_mario->GetPosition().x > SCREEN_WIDTH * 0.6)
	//{
	//	camera.x += MOVEMENTSPEED;

	//	CharacterMario* clone_mario = character_mario;
	//	Vector2D position = clone_mario->GetPosition();
	//	clone_mario->SetPosition(position).x -= MOVEMENTSPEED * deltaTime;

	//	//Make a copy of character mario then set his position;
	//}
}

void GameScreenLevel1::Render() 
{
	m_background_texture->Render(Vector2D(), /*camera*/ SDL_FLIP_NONE);

	for (int i = 0; i < m_enemies.size(); i++) 
	{
		m_enemies[i]->Render(/*camera*/);
	}

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	character_mario->Render(/*camera*/);
	character_luigi->Render(/*camera*/);
	m_pow_block->Render(/*camera*/);
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

	SetLevelMap();

	m_pow_block = new PowBlock(m_renderer, m_level_map);

	CreateKoopa(Vector2D(150, 32), FACING_LEFT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	CreateCoins(Vector2D(160, 128));
	CreateCoins(Vector2D(192, 128));
	CreateCoins(Vector2D(224, 128));
	CreateCoins(Vector2D(256, 128));
	CreateCoins(Vector2D(288, 128));
	CreateCoins(Vector2D(320, 128));

	character_mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	character_luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 330), m_level_map);
}

void GameScreenLevel1::SetLevelMap() 
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

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

	for (unsigned int j = 0; j < m_enemies.size(); j++) 
	{
		if (m_enemies[j]->GetAlive()) 
		{
			m_enemies[j]->TakeDamage();
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e) 
{
	if (!m_enemies.empty())
	{
		if (enemyIndexToDelete != -1) 
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
			enemyIndexToDelete = -1;
		}

		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
				{
					m_enemies[i]->SetAlive(false);
				}
			}

			m_enemies[i]->Update(deltaTime, e);

			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{

			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], character_mario))
				{
					if (m_enemies[i]->GetAlive() == true)
					{
						character_mario->MarioDeath();
					}
					else
					{
						enemyIndexToDelete = i;
					}

				}

				if (Collisions::Instance()->Circle(m_enemies[i], character_luigi))
				{
					if (m_enemies[i]->GetAlive() == true)
					{
						character_luigi->LuigiDeath();
					}
					else
					{
						enemyIndexToDelete = i;
					}

				}
			}

		}
	}

}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty()) 
	{
		if (coinIndexToDelete != -1) 
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
			coinIndexToDelete = -1;
		}

		for (unsigned int i = 0; i < m_coins.size(); i++) 
		{
			if (Collisions::Instance()->Box(m_coins[i]->GetCollisionBox(), character_mario->GetCollisionBox())) 
			{
				coinIndexToDelete = i;
			}
			else if (Collisions::Instance()->Box(m_coins[i]->GetCollisionBox(), character_luigi->GetCollisionBox()))
			{
				coinIndexToDelete = i;
			}

			m_coins[i]->Update(deltaTime, e);
		}
	}
}

void GameScreenLevel1::CreateCoins(Vector2D position)
{
	m_Coin = new Coin(m_renderer, "Images/Coin.png", position, m_level_map);
	m_coins.push_back(m_Coin);
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	Koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_enemies.push_back(Koopa);
}
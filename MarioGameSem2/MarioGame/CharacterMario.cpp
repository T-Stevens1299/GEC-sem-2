#include "CharacterMario.h"

#include "Texture2D.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{

}

CharacterMario::~CharacterMario() 
{

}

void CharacterMario::Render()
{
	Character::Render();
}

void CharacterMario::Update(float deltaTime, SDL_Event e) 
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{

		case SDLK_a:
			m_moving_left = true;
			break;

		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_SPACE:
			if (m_can_jump) 
			{
				Character::Jump();
			}
			break;

		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{

		case SDLK_a:
			m_moving_left = false;
			break;

		case SDLK_d:
			m_moving_right = false;
			break;

		}
		break;
	}

	if (marioDead == false)
	{
		Character::Update(deltaTime, e);
	}
	else
	{
		m_position.y += deltaTime * GRAVITY * 3;
	}
}

void CharacterMario::MoveLeft(float deltaTime)
{
	if (m_moving_left == true)
	{
		m_position.x -= deltaTime * MOVEMENTSPEED;
		m_facing_direction = FACING_LEFT;
	}
}

void CharacterMario::MoveRight(float deltaTime)
{
	if (m_moving_right == true)
	{
		m_position.x += deltaTime * MOVEMENTSPEED;
		m_facing_direction = FACING_RIGHT;
	}
}

void CharacterMario::MarioDeath() 
{
	if (!m_jumping) 
	{
		m_jumping = true;
		marioDead = true;
	}
}
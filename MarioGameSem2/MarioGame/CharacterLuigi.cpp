#include "CharacterLuigi.h"
#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position) : Character(renderer, imagePath, start_position)
{

}

CharacterLuigi::~CharacterLuigi()
{

}

void CharacterLuigi::Render()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{

		case SDLK_LEFT:
			m_moving_left = true;
			break;

		case SDLK_RIGHT:
			m_moving_right = true;
			break;

		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{

		case SDLK_LEFT:
			m_moving_left = false;
			break;

		case SDLK_RIGHT:
			m_moving_right = false;
			break;

		}
		break;
	}

	Character::Update(deltaTime, e);
}

void CharacterLuigi::MoveLeft(float deltaTime)
{
	if (m_moving_left == true)
	{
		m_position.x -= deltaTime * MOVEMENTSPEED;
		m_facing_direction = FACING_LEFT;
	}
}

void CharacterLuigi::MoveRight(float deltaTime)
{
	if (m_moving_right == true)
	{
		m_position.x += deltaTime * MOVEMENTSPEED;
		m_facing_direction = FACING_RIGHT;
	}
}

void CharacterLuigi::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D CharacterLuigi::GetPosition()
{
	return m_position;
}
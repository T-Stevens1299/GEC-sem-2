#include "CharacterLuigi.h"

#include "Texture2D.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{

}

CharacterLuigi::~CharacterLuigi()
{

}

void CharacterLuigi::Render()
{
	Character::Render();
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
		case SDLK_UP:
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

//void CharacterLuigi::SetPosition(Vector2D new_position)
//{
//	m_position = new_position;
//}
//
//Vector2D CharacterLuigi::GetPosition()
//{
//	return m_position;
//}
//
//void CharacterLuigi::AddGravity(float deltaTime)
//{
//	if (m_position.y + 64 <= SCREEN_HEIGHT)
//	{
//		m_position.y += GRAVITY * deltaTime;
//	}
//	else
//	{
//		m_can_jump = true;
//	}
//}
//
//void CharacterLuigi::Jump()
//{
//	if (!m_jumping)
//	{
//		m_jump_force = INITIAL_JUMP_FORCE;
//		m_jumping = true;
//		m_can_jump = false;
//	}
//}
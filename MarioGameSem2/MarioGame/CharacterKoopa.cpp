#include "CharacterKoopa.h"

#include "Texture2D.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;
	isAlive = true;
	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture-> GetHeight();
}

CharacterKoopa::~CharacterKoopa()
{

}

void CharacterKoopa::Render()
{
	int left = 0.0f;

	if (m_injured) 
	{
		left = m_single_sprite_w;
	}

	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT) 
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else 
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (!m_injured)
	{
		if (m_facing_direction == FACING_LEFT) 
		{
			m_moving_left = true;
			m_moving_right = false;
			
		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_left = false;
			m_moving_right = true;
			
		}
	}
	else
	{
		m_moving_right = true;
		m_moving_left = false;

		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0) 
		{
			FlipRightWayUp();
		}			
	}

	Character::Update(deltaTime, e);

	//Moves the Koopa in the opposite direction if it hits the screen edge
	if (m_position.x < 0) 
	{
		m_moving_left = true;
		m_moving_right = false;
		m_facing_direction = FACING_RIGHT;
		m_position.x = 0;
	}
	else if (m_position.x > SCREEN_WIDTH - m_single_sprite_w) 
	{
		m_moving_left = false;
		m_moving_right = true;
		m_facing_direction = FACING_LEFT;
		m_position.x = SCREEN_WIDTH - m_single_sprite_w;
	}

}

void CharacterKoopa::TakeDamage()
{
	m_injured = true;
	m_injured_time = INURED_TIME;
	isAlive = false;
	Jump();
}

void CharacterKoopa::Jump()
{
	if (!m_jumping) 
	{
		m_jump_force = JUMP_FORCE_KOOPA;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterKoopa::SetAlive(bool m_is_injured) 
{
	m_injured = m_is_injured;
}

void CharacterKoopa::FlipRightWayUp() 
{
	m_facing_direction = FACING_RIGHT;
	isAlive = true;
	m_injured = false;
	Jump();
}
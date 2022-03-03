#include "Character.h"
#include "Texture2D.h"
#include "constants.h"
using namespace std;

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position) 
{
	m_renderer = renderer;
	m_position = start_position;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath)) 
	{
		cout << "Failed to load background texture!" << endl;
	}

	m_facing_direction = FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;

	m_collision_radius = 15.0f;

}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render() 
{
	if (m_facing_direction == FACING_RIGHT) 
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else 
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if(m_moving_left) 
	{
		MoveLeft(deltaTime);
	}
	else if(m_moving_right)
	{
		MoveRight(deltaTime);
	}


	switch (e.key.keysym.sym)
	{

	case SDLK_a:
		m_moving_left = true;

		/*m_position.x -= 1;
		m_facing_direction = FACING_LEFT;*/
	break;
	
	case SDLK_d:
		m_moving_right = true;

		/*m_position.x -= -1;
		m_facing_direction = FACING_RIGHT;*/
	break;

	}
}

void Character::MoveLeft(float deltaTime) 
{
	if (m_moving_left == true) 
	{
		m_position.x -= deltaTime * MOVEMENTSPEED;
			m_facing_direction = FACING_LEFT;
	}
}

void Character::MoveRight(float deltaTime)
{
	if (m_moving_right == true)
	{
		m_position.x += deltaTime * MOVEMENTSPEED;
			m_facing_direction = FACING_RIGHT;
	}
}

void Character::SetPosition(Vector2D new_position) 
{
	m_position = new_position;
}

Vector2D Character::GetPosition() 
{
	return m_position;
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}
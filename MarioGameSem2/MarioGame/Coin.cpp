#include "Coin.h"
#include "Texture2D.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	m_position = startPosition;
	imagePath = "Images/Coin.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imagePath.c_str())) 
	{
		std::cout << "Failed to load texture" << imagePath << std::endl;
		return;
	}

	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

Coin::~Coin() 
{

}

void Coin::Update(float deltaTime, SDL_Event e) 
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}
}

void Coin::Render() 
{
	int left = m_single_sprite_w * m_current_frame;
	SDL_Rect portionOfSpriteSheet = { left, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };
	m_texture->Render(portionOfSpriteSheet, destRect, SDL_FLIP_NONE);
}

Rect2D Coin::GetCollisionBox() 
{
	return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_texture->GetHeight());
}
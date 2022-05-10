#pragma once

#include <SDL.h>
#include "Character.h"
#include "Collisions.h"

class Texture2D;

class Coin : public Character
{
public:
	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Coin();
	Rect2D GetCollisionBox();
	void Update(float deltaTime, SDL_Event e);
	void Render();
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_movement_speed;
	float m_frame_delay;
	int m_current_frame;

};
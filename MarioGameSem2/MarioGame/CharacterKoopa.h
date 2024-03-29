#pragma once
#ifndef _CHARACTERKOOPA_
#define _CHARACTERKOOPA_

#include <iostream>
#include <string>

#include <SDL.h>

#include "Character.h"

class Texture2D;

class CharacterKoopa : public Character 
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void Jump() override;
	void TakeDamage();
	void SetAlive(bool mIsAlive);
	bool GetAlive() { return isAlive; };


	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_movement_speed;

private:
	void FlipRightWayUp();

	FACING m_facing_direction;

	bool isAlive;
	bool m_injured;
	float m_injured_time;
};

#endif
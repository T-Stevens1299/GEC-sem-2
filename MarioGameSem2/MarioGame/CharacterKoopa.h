#pragma once
#ifndef _CHARACTERKOOPA_
#define _CHARACTERKOOPA_

#include <SDL.h>
#include <iostream>
#include <string>
#include "Character.h"

class CharacterKoopa : public Character 
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void Jump();
	void TakeDamage();

	bool GetInjured() { return m_injured; };

	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_movement_speed;

private:
	void FlipRightWayUp();

	FACING m_facing_direction;

	bool m_injured;
	float m_injured_time;
};

#endif
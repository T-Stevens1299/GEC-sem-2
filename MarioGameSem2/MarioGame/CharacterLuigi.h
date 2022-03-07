#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include <SDL.h>
#include <iostream>
#include <string>
#include "Character.h"

class Texture2D;

class CharacterLuigi : public Character
{

public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	virtual void Jump();
	virtual void AddGravity(float deltaTime);

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
private:
	FACING m_facing_direction;
};

#endif
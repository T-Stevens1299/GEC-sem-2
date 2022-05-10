#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include <iostream>
#include <string>
#include <SDL.h>
#include "Character.h"

class Texture2D;

class CharacterLuigi : public Character
{

public:
	CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	void Render(/*SDL_Rect Camera*/);
	void Update(float deltaTime, SDL_Event e);

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	void LuigiDeath();

	bool luigiDead = false;

	//virtual void Jump();
	//void AddGravity(float deltaTime);

	//void SetPosition(Vector2D new_position);
	//Vector2D GetPosition();
private:
	FACING m_facing_direction;
};

#endif
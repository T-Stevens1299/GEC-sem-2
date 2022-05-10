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

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	//Kills Luigi
	void LuigiDeath();
	bool luigiDead = false;
private:
	FACING m_facing_direction;
};

#endif
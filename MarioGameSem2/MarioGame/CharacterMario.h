#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include <iostream>
#include <string>
#include <SDL.h>
#include "Character.h"

class Texture2D;

class CharacterMario : public Character
{

public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	//Kills Mario
	void MarioDeath();
	bool marioDead = false;
private:
	FACING m_facing_direction;
};

#endif
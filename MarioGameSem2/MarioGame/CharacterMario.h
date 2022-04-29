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

	//virtual void Jump();
	//void AddGravity(float deltaTime);

	//void SetPosition(Vector2D new_position);
	//Vector2D GetPosition();
private:
	FACING m_facing_direction;
};

#endif
#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include <SDL.h>
#include <iostream>
#include <string>
#include "Character.h"

class Texture2D;

class CharacterMario : public Character
{

public:
	CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position);
	~CharacterMario();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
private:
	FACING m_facing_direction;
};

#endif
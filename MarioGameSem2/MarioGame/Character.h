#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <iostream>

#include <SDL.h>

#include "Commons.h"
#include "constants.h"
#include "LevelMap.h"

class Texture2D;

using namespace std;

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

	bool m_moving_left;
	bool m_moving_right;

	bool m_jumping;
	bool m_can_jump;

	bool m_alive;

	float m_jump_force;

	float m_collision_radius;

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);

	void AddGravity(float deltaTime);
	
	virtual void Jump();

	void CancelJump() {m_jumping = false;}
	bool isJumping() {return m_jumping;}

	void SetAlive(bool isAlive);

	bool GetAlive() { return m_alive; };

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();

	Rect2D GetCollisionBox();

private:
	FACING m_facing_direction;

	LevelMap* m_current_level_map;
};

#endif
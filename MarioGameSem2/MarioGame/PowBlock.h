#pragma once
#ifndef _POWBLOCK_H
#define _POWBLOCK_H

#include "Texture2D.h"
#include "LevelMap.h"
#include "Commons.h"
#include "SDL.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	void TakeHit();
	void Render();

	inline bool isAvailable() { return m_num_hits_left > 0; }

	inline Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
private:
	SDL_Renderer* m_renderer;   
	Vector2D m_position;
	Texture2D* m_texture;
	LevelMap* m_level_map;

	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_num_hits_left;
};

#endif
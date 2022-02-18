#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

bool InitSDL();
void CloseSDL();
void Render();
//SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();

bool Update()
{
	SDL_Event e;

	SDL_PollEvent(&e);

	switch (e.type)
	{

	case SDL_QUIT:
		return true;
		break;
	}

	return false;
}


int main(int argc, char* args[])
{
	bool quit = false;

	if (InitSDL())
	{

		while (!quit)
		{
			Render();
			quit = Update();
		}

		CloseSDL();
	}
	return 0;
}

bool InitSDL() 
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else 
	{

		// HERE

		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (g_window == nullptr) 
		{
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

		if (g_window != nullptr) 
		{
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags)) 
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else 
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		g_texture = new Texture2D(g_renderer);
		if (!g_texture->LoadFromFile("Images/test.bmp"))
		{
			return false;
		}

		if (g_texture == nullptr) 
		{
			return false;
		}

		return true;
	}

}

void Render() 
{
	//CLear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);
	
	g_texture->Render(Vector2D(), SDL_FLIP_NONE);

	SDL_RenderPresent(g_renderer);
	
	
	/*SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

	SDL_RenderPresent(g_renderer);*/
}

//SDL_Texture* LoadTextureFromFile(string path) 
//{
//	FreeTexture();
//
//	SDL_Texture* p_texture = nullptr;
//
//	SDL_Surface* p_surface = IMG_Load(path.c_str());
//	if (p_surface != nullptr) 
//	{
//		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
//		if (p_texture == nullptr) 
//		{
//			cout << "Unable to create texture from surface. Error: " << SDL_GetError();
//		}
//	}
//	SDL_FreeSurface(p_surface);
//
//	return p_texture;
//}

//void FreeTexture() 
//{
//	if (g_texture != nullptr)
//	{
//		SDL_DestroyTexture(g_texture);
//		g_texture = nullptr;
//	}
//}

void CloseSDL() 
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//FreeTexture();
	//SDL_DestroyRenderer(g_renderer);
	//g_renderer = nullptr;

	IMG_Quit();
	SDL_Quit();

	delete g_texture;
	g_texture = nullptr;
}
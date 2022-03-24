#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
//Mix_Music* g_music = nullptr;

bool InitSDL();
void CloseSDL();
void Render();
//void LoadMusic();

bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type)
	{

		case SDL_QUIT:
			return true;
		break;
	}
	switch (e.key.keysym.sym)
	{

	case SDLK_q:
		return true;
	break;

	}

	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);

	g_old_time = new_time;

	return false;
}


int main(int argc, char* args[])
{
	if (InitSDL())
	{
		/*Mix_LoadMUS("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0) 
		{
			Mix_PlayMusic(g_music, -1);
		}*/
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		g_old_time = SDL_GetTicks();

		bool quit = false;

		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CloseSDL();

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

		g_window = SDL_CreateWindow("Budget Mario Bros!",
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

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 
		{
			cout << "Mixer could not init. Error: " << Mix_GetError();
		}

		return true;
	}

}

void Render() 
{
	//CLear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);
	
	game_screen_manager->Render();

	SDL_RenderPresent(g_renderer);
	
}

void CloseSDL() 
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	IMG_Quit();
	SDL_Quit();

	/*Mix_FreeMusic(g_music);
	g_music = nullptr;*/
	
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;

	delete game_screen_manager;
	game_screen_manager = nullptr;
}

//void LoadMusic() 
//{
//	g_music = Mix_LoadMUS(path.c_str());
//	if (g_music == nullptr) 
//	{
//		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
//	}
//}
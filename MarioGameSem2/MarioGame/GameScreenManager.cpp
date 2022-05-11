#include "GameScreen.h"
#include "GameScreenIntro.h"
#include "GameScreenLevel1.h"
#include "GameScreenManager.h"
#include "GameScreenLose.h"
#include "GameScreenWin.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) 
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager() 
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render() 
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e) 
{
	m_current_screen->Update(deltaTime, e);

	if (m_current_screen->GetScreenToChange() != SCREEN_NULL)
	{
		ChangeScreen(m_current_screen->GetScreenToChange());
	}
}

void GameScreenManager::ChangeScreen(SCREENS new_screen) 
{
	if (m_current_screen != nullptr) 
	{
		delete m_current_screen;
	}

	GameScreenIntro* intro;
	GameScreenLevel1* level1;
	GameScreenLose* Lose;
	GameScreenWin* WinScreen;

	switch (new_screen)
	{
	case SCREEN_NULL:

		break;

	case SCREEN_MENU:
		intro = new GameScreenIntro(m_renderer);
		m_current_screen = (GameScreen*)intro;
		intro = nullptr;
		break;

	case SCREEN_LEVEL1:
		level1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)level1;
		level1 = nullptr;
		break;
	case SCREEN_GAMEOVER:
		Lose = new GameScreenLose(m_renderer);
		m_current_screen = (GameScreen*)Lose;
		Lose = nullptr;
		break;
	case SCREEN_WIN:
		WinScreen = new GameScreenWin(m_renderer);
		m_current_screen = (GameScreen*)WinScreen;
		WinScreen = nullptr;
		break;

	default: ;	
	}
}
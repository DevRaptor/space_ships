#include "GameEngine.h"

GameEngine::GameEngine()
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Space ships", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, 0);
	

	state = std::make_unique<GameState>();

}

GameEngine::~GameEngine()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameEngine::Update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit = true;
	}

}



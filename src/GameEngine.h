#pragma once

#include <memory>

#include <SDL.h>
#include <glm\glm.hpp>

#include "GameState.h"

class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	void Update();

	bool IsExit() { return exit; }



private:
	bool exit = false;

	std::unique_ptr<GameState> state;

	SDL_Window* window;
};
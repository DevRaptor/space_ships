#pragma once

#include <memory>

#include <SDL.h>
#include <glm\glm.hpp>

#include "GameState.h"

#define GLEW_STATIC //needed to static link GLEW

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

	SDL_GLContext context;

	int resolution_x = 800;
	int resolution_y = 600;
};
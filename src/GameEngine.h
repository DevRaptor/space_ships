#pragma once

#include <memory>

#include <SDL.h>
#include <glm\glm.hpp>

#include "GameState.h"

#define GLEW_STATIC //needed to static link GLEW



class GameEngine
{
	using Clock = std::chrono::high_resolution_clock;

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

	std::chrono::nanoseconds lag;

	std::chrono::steady_clock::time_point time_start;

	void HandleEvents();

};
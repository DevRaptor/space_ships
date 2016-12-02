#pragma once

#include <chrono>

#include <SDL.h>

class GameState
{
public:
	GameState();
	~GameState();

	void Update(std::chrono::nanoseconds delta_time);

private:

	//game objects
};

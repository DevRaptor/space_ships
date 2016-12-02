#pragma once

#include <chrono>
#include <memory>

#include <SDL.h>

#include "entity/Entity.h"

class GameState
{
public:
	GameState();
	~GameState();

	void Update(std::chrono::nanoseconds delta_time);

private:

	std::shared_ptr<Entity> ship;
	std::shared_ptr<Entity> meteors;
	std::shared_ptr<Entity> bullets;
};

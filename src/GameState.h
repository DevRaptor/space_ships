#pragma once

#include <chrono>
#include <memory>

#include <SDL.h>

#include <btBulletDynamicsCommon.h>

#include "entity/Entity.h"

class Renderer;

class GameState
{
	friend class Renderer;

public:
	GameState();
	~GameState();

	void Update(std::chrono::milliseconds delta_time);

private:

	std::shared_ptr<Entity> ship;
	std::shared_ptr<Entity> meteors;
	std::shared_ptr<Entity> bullets;

	//physics
	std::unique_ptr<btBroadphaseInterface> broad_phase;
	std::unique_ptr<btDefaultCollisionConfiguration> collision_config;
	std::unique_ptr<btCollisionDispatcher> dispatcher;
	std::unique_ptr<btSequentialImpulseConstraintSolver> solver;
	std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld;

};

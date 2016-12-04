#include "GameState.h"

#include <iostream>

#include "entity/Ship.h"

GameState::GameState()
{
	broad_phase = std::make_unique<btDbvtBroadphase>();
	collision_config = std::make_unique<btDefaultCollisionConfiguration>();
	dispatcher = std::make_unique<btCollisionDispatcher>(collision_config.get());
	solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(dispatcher.get(), broad_phase.get(), 
		solver.get(), collision_config.get());

	dynamicsWorld->setGravity(btVector3(0, 0, 0));


	ship = std::make_shared<Ship>(dynamicsWorld, glm::vec3(0, -2, 0));
}

GameState::~GameState()
{
}

void GameState::Update(std::chrono::milliseconds delta_time)
{
	float delta = delta_time.count() / 1000.0f;
	dynamicsWorld->stepSimulation(delta, 10);

	ship->Update();
}
#include "GameState.h"

#include <iostream>

#include "entity/Meteor.h"
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

	for (auto obj : meteors)
		obj->Update();

	for (auto obj : bullets)
		obj->Update();

	if (GameModule::input->GetKeyState(SDL_SCANCODE_Q))
	{
		meteors.push_back(std::make_shared<Meteor>(dynamicsWorld, glm::vec3(-10, 0, 0), 
			glm::vec3(1.0f, 2.0f, 1.0f)));
	}
}
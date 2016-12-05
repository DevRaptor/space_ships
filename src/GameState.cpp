#include "GameState.h"

#include <iostream>

#include "entity/Meteor.h"
#include "entity/Ship.h"
#include "utility/Log.h"

GameState::GameState()
{
	meteor_data.pos_x = -GameModule::resources->GetFloatParameter("camera_pos_y");
	meteor_data.pos_z = GameModule::resources->GetFloatParameter("camera_pos_y") / 2.0f;

	meteor_data.scale_min = GameModule::resources->GetFloatParameter("meteor_scale_min");
	meteor_data.scale_max = GameModule::resources->GetFloatParameter("meteor_scale_max");
	meteor_data.distortion = GameModule::resources->GetFloatParameter("meteor_max_distortion");



	broad_phase = std::make_unique<btDbvtBroadphase>();
	collision_config = std::make_unique<btDefaultCollisionConfiguration>();
	dispatcher = std::make_unique<btCollisionDispatcher>(collision_config.get());
	solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	dynamic_world = std::make_shared<btDiscreteDynamicsWorld>(dispatcher.get(), broad_phase.get(),
		solver.get(), collision_config.get());

	dynamic_world->setGravity(btVector3(0, 0, 0));

	InitGameplay();
}

GameState::~GameState()
{
}

void GameState::Update(std::chrono::milliseconds delta_time)
{
	float delta = delta_time.count() / 1000.0f; //in seconds
	dynamic_world->stepSimulation(delta, 10);

	if (ship)
	{
		ship->Update();

		//must check collisions between ship and meteors
		dynamic_world->contactTest(ship->GetRigidBody(), callback);

		if (ship->IsDestroyed())
			RestartGameplay();
	}
	else
		RestartGameplay();


	auto it = bullets.begin();
	while (it != bullets.end())
	{
		if ((*it)->IsDestroyed())
		{
			it = bullets.erase(it);
		}
		else
		{
			(*it)->Update();

			//must check collisions between bullets and meteors
			dynamic_world->contactTest((*it)->GetRigidBody(), callback);

			++it;
		}
	}


	auto iter = meteors.begin();
	while (iter != meteors.end())
	{
		(*iter)->Update();

		if ((*iter)->IsDestroyed())
			iter = meteors.erase(iter);
		else
			++iter;
	}


	if (std::chrono::high_resolution_clock::now() > meteor_data.timer)
	{
		SpawnMeteor();
		meteor_data.timer = std::chrono::high_resolution_clock::now() + meteor_data.delay;
	}


	static std::chrono::high_resolution_clock::time_point restart_timer = std::chrono::high_resolution_clock::now();
	if (GameModule::input->GetKeyState(SDL_SCANCODE_R)
		&& (std::chrono::high_resolution_clock::now() > restart_timer))
	{
		RestartGameplay();

		restart_timer = std::chrono::high_resolution_clock::now() + std::chrono::seconds(1);
	}
}

void GameState::SpawnMeteor()
{
	std::uniform_real_distribution<> random_distortion(1.0f, meteor_data.distortion);
	std::uniform_real_distribution<> random_scale(meteor_data.scale_min, meteor_data.scale_max);
	float size = random_scale(GameModule::random_gen);

	glm::vec3 scale(size, size, size * random_distortion(GameModule::random_gen));

	std::uniform_real_distribution<> rand_pos_z(-meteor_data.pos_z, meteor_data.pos_z);

	//must lower meteor position by half of size
	glm::vec3 pos(meteor_data.pos_x, -size / 2.0f, rand_pos_z(GameModule::random_gen));

	auto meteor = std::make_shared<Meteor>(dynamic_world, pos, scale);
	meteor->Init();
	meteors.push_back(meteor);
}

void GameState::InitGameplay()
{
	meteor_data.delay = std::chrono::milliseconds(GameModule::resources->GetIntParameter("meteor_delay"));

	ship = std::make_shared<Ship>(dynamic_world, glm::vec3(0, 0, 0), bullets);
	ship->Init();
}

void GameState::RestartGameplay()
{
	Logger::Log("Restart gameplay\n");

	ship.reset();
	meteors.clear();
	bullets.clear();

	InitGameplay();
}

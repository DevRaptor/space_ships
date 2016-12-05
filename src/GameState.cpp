#include "GameState.h"

#include <iostream>

#include "entity/Meteor.h"
#include "entity/Ship.h"

GameState::GameState()
{
	meteor_data.pos_x = -GameModule::resources->GetFloatParameter("camera_pos_y");
	meteor_data.pos_z = GameModule::resources->GetFloatParameter("camera_pos_y") / 2.0f;

	meteor_data.scale_min = GameModule::resources->GetFloatParameter("meteor_scale_min");
	meteor_data.scale_max = GameModule::resources->GetFloatParameter("meteor_scale_max");
	meteor_data.distortion = GameModule::resources->GetFloatParameter("meteor_max_distortion");
	
	meteor_data.delay = std::chrono::milliseconds(GameModule::resources->GetIntParameter("meteor_delay"));

	broad_phase = std::make_unique<btDbvtBroadphase>();
	collision_config = std::make_unique<btDefaultCollisionConfiguration>();
	dispatcher = std::make_unique<btCollisionDispatcher>(collision_config.get());
	solver = std::make_unique<btSequentialImpulseConstraintSolver>();

	dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(dispatcher.get(), broad_phase.get(), 
		solver.get(), collision_config.get());

	dynamicsWorld->setGravity(btVector3(0, 0, 0));


	ship = std::make_shared<Ship>(dynamicsWorld, glm::vec3(0, 0, 0), bullets);
}

GameState::~GameState()
{
}

void GameState::Update(std::chrono::milliseconds delta_time)
{
	float delta = delta_time.count() / 1000.0f; //in seconds
	dynamicsWorld->stepSimulation(delta, 10);

	ship->Update();

	for (auto obj : meteors)
		obj->Update();

	for (auto obj : bullets)
		obj->Update();

	if (std::chrono::high_resolution_clock::now() > meteor_data.timer)
	{
		SpawnMeteor();
		meteor_data.timer = std::chrono::high_resolution_clock::now() + meteor_data.delay;
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

	meteors.push_back(std::make_shared<Meteor>(dynamicsWorld, pos, scale));
}

#pragma once

#include <chrono>

#include "entity/Entity.h"

class Ship : public Entity
{
public:
	Ship(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr, glm::vec3 start_pos);
	~Ship();

	void Update() override;

protected:
	float move_speed;
	float move_speed_max;

	float move_damping;
	float stop_damping;

	float movement_limit;

	int shoot_delay; //time to next shoot, in ms
	std::chrono::steady_clock::time_point shoot_timer;

	void Shoot();
};


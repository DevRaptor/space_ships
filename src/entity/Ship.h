#pragma once

#include "entity/Entity.h"

class Ship : public Entity
{
public:
	Ship(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr, glm::vec3 start_pos);
	~Ship();

	void Update() override;

protected:
	float move_speed;
};


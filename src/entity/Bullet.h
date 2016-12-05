#pragma once

#include "entity/Entity.h"

class Bullet : public Entity
{
public:
	Bullet(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr, 
		std::shared_ptr<Entity> owner_object,
		glm::vec3 start_pos, glm::vec3 scale);
	~Bullet();

	void Update() override;

protected:
	std::weak_ptr<Entity> owner;
};


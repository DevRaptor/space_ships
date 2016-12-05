#pragma once

#include "entity/Entity.h"

class Bullet : public Entity, public std::enable_shared_from_this<Bullet>
{
public:
	Bullet(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr,
		glm::vec3 start_pos, glm::vec3 scale);
	~Bullet();

	void Init() override;
	void Update() override;

};


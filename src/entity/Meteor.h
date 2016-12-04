#pragma once

#include "entity/Entity.h"

class Meteor : public Entity
{
public:
	Meteor(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr, 
		glm::vec3 start_pos, glm::vec3 scale);
	~Meteor();

	void Update() override;

protected:

	btVector3 velocity;
	btVector3 rotation;
};


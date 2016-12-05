#pragma once

#include <iostream>
#include <memory>

#include <btBulletDynamicsCommon.h>

#include "rendering/Mesh.h"
#include "GameModule.h"
#include "entity/PhysicBody.h"

//EntityType declaration in PhysicBody

class Entity
{
public:
	glm::mat4 transform_mat;

	Entity(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr,
		glm::vec3 start_pos, glm::vec3 init_scale)
		: world(world_ptr), pos(start_pos), scale(init_scale),
		destroyed(false)
	{
		type = EntityType::NONE;
	}

	virtual ~Entity() { }

	virtual void Init() = 0;
	virtual void Update() = 0;

	virtual void Draw()
	{
		if (mesh)
		{
			mesh->Draw();
		}
	}

	EntityType GetType() { return type; }

	void Destroy() { destroyed = true; }
	bool IsDestroyed() { return destroyed; }

	RigidBody* GetRigidBody() { return physic_body->body.get(); }

	std::unique_ptr<PhysicBody> physic_body;

protected:
	EntityType type;

	std::shared_ptr<Mesh> mesh;

	std::weak_ptr<btDiscreteDynamicsWorld> world;
	glm::vec3 pos;
	glm::vec3 scale;
	bool destroyed;
};

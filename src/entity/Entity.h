#pragma once

#include <iostream>
#include <memory>

#include <btBulletDynamicsCommon.h>

#include "rendering/Mesh.h"
#include "GameModule.h"
#include "entity/PhysicBody.h"

enum class EntityType
{
	SHIP, 
	METEOR,
	BULLET,
	NONE
};

class Entity
{
public:
	glm::mat4 transform_mat;

	Entity(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr)
	{
		type = EntityType::NONE;
		mesh = GameModule::resources->GetMesh("cube");
		physic_body = std::make_unique<PhysicBody>(world_ptr);
	}

	virtual ~Entity() { }

	virtual void Update() 
	{
		transform_mat = physic_body->GetTransformMatrix();

		/*
		btTransform trans;
		body->getMotionState()->getWorldTransform(trans);
		std::cout << "debug: " << trans.getOrigin().getY() << std::endl;
		*/
	}

	virtual void Draw()
	{
		if (mesh)
		{
			mesh->Draw();
		}
	}

	EntityType GetType() { return type; }


protected:
	EntityType type;

	std::shared_ptr<Mesh> mesh;
	std::unique_ptr<PhysicBody> physic_body;
};

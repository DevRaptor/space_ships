#pragma once

#include <iostream>
#include <memory>

#include <btBulletDynamicsCommon.h>

#include "rendering/Mesh.h"
#include "GameModule.h"

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
	Entity(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr)
		: world(world_ptr)
	{
		type = EntityType::NONE;

		mesh = GameModule::resources->GetMesh("cube");

		motion_state = std::make_unique<btDefaultMotionState>
			(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
		btScalar mass = 1;
		btVector3 inertia(0, 0, 0);
		collision_shape = std::make_unique<btSphereShape>(1);
		collision_shape->calculateLocalInertia(mass, inertia);
		btRigidBody::btRigidBodyConstructionInfo body_info(mass, motion_state.get(), 
			collision_shape.get(), inertia);
		body = std::make_unique<btRigidBody>(body_info);

		world_ptr->addRigidBody(body.get());
	}
	virtual ~Entity()
	{ 
		if(auto ptr = world.lock())
			ptr->removeRigidBody(body.get());
	}

	virtual void Update() 
	{
		btTransform transform;
		body->getMotionState()->getWorldTransform(transform);
		float matrix[16];
		transform.getOpenGLMatrix(matrix);
		transform_mat = glm::make_mat4(matrix);

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


	glm::mat4 transform_mat;

protected:
	EntityType type;

	std::shared_ptr<Mesh> mesh;

	std::unique_ptr<btRigidBody> body;
	std::unique_ptr<btDefaultMotionState> motion_state;
	std::unique_ptr<btCollisionShape> collision_shape;

private:
	std::weak_ptr<btDiscreteDynamicsWorld> world;
};

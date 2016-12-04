#pragma once

#include <btBulletDynamicsCommon.h>

class PhysicBody
{
public:
	std::unique_ptr<btRigidBody> body;

	PhysicBody(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr)
		: world(world_ptr)
	{
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

	~PhysicBody()
	{
		if (auto ptr = world.lock())
			ptr->removeRigidBody(body.get());
	}

	glm::mat4 GetTransformMatrix()
	{
		btTransform transform;
		body->getMotionState()->getWorldTransform(transform);
		float matrix[16];
		transform.getOpenGLMatrix(matrix);

		return glm::make_mat4(matrix);
	}

private:
	std::unique_ptr<btDefaultMotionState> motion_state;
	std::unique_ptr<btCollisionShape> collision_shape;

	std::weak_ptr<btDiscreteDynamicsWorld> world;
};
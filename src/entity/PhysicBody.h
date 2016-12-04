#pragma once

#include <btBulletDynamicsCommon.h>

#include <glm/gtc/matrix_transform.hpp>

class PhysicBody
{
public:
	std::unique_ptr<btRigidBody> body;
	glm::vec3 scale;

	PhysicBody(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr, glm::vec3 pos, glm::vec3 body_scale)
		: world(world_ptr), scale(body_scale)
	{
		motion_state = std::make_unique<btDefaultMotionState>
			(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));
		btScalar mass = 1.0f;
		btVector3 inertia(0, 0, 0);
		//collision_shape = std::make_unique<btSphereShape>(1.0f);
		collision_shape = std::make_unique<btBoxShape>(btVector3(scale.x, scale.y, scale.z));
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

		glm::mat4 mat = glm::make_mat4(matrix) * glm::scale(glm::mat4(1.0f), scale);
		return mat;
	}

private:
	std::unique_ptr<btDefaultMotionState> motion_state;
	std::unique_ptr<btCollisionShape> collision_shape;

	std::weak_ptr<btDiscreteDynamicsWorld> world;
};
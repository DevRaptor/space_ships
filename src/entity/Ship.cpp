#include "Ship.h"

Ship::Ship(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr, glm::vec3 start_pos)
	: Entity(world_ptr)
{
	type = EntityType::SHIP;

	move_speed = GameModule::resources->GetFloatParameter("ship_move_speed");
	move_damping = GameModule::resources->GetFloatParameter("ship_move_damping");
	stop_damping = GameModule::resources->GetFloatParameter("ship_stop_damping");

	move_speed_max = GameModule::resources->GetFloatParameter("ship_move_speed_max");

	// min/max world position
	movement_limit = (GameModule::resources->GetFloatParameter("camera_pos_y") / 2.0f) * 0.8f;

	//only left/right movement
	physic_body->body->setLinearFactor(btVector3(0, 0, 1));

	//disable rotation
	physic_body->body->setAngularFactor(btVector3(0, 0, 0));
}

Ship::~Ship()
{
}

void Ship::Update()
{
	transform_mat = physic_body->GetTransformMatrix();

	btTransform transform;
	physic_body->body->getMotionState()->getWorldTransform(transform);
	btVector3 pos = transform.getOrigin();
	
	if (pos.getZ() < movement_limit &&
		(GameModule::input->GetKeyState(SDL_SCANCODE_LEFT)
		|| GameModule::input->GetKeyState(SDL_SCANCODE_A)))
	{
		physic_body->body->activate(true);

		btVector3 impulse(0.0f, 0.0f, move_speed);
		physic_body->body->applyCentralImpulse(impulse);
		
		physic_body->body->setDamping(move_damping, 0);
	}
	else if (pos.getZ() > -movement_limit &&
		(GameModule::input->GetKeyState(SDL_SCANCODE_RIGHT)
		|| GameModule::input->GetKeyState(SDL_SCANCODE_D)))
	{
		physic_body->body->activate(true);

		btVector3 impulse(0.0f, 0.0f, -move_speed);
		physic_body->body->applyCentralImpulse(impulse);
		physic_body->body->setDamping(move_damping, 0);
	}
	else
	{
		physic_body->body->setDamping(stop_damping, 0);
	}
	
	btVector3 velocity = physic_body->body->getLinearVelocity();
	if (velocity.length() > move_speed_max)
	{
		velocity *= move_speed_max / velocity.length();
		physic_body->body->setLinearVelocity(velocity);
	}
}

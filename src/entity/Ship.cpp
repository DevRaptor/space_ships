#include "Ship.h"

Ship::Ship(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr, glm::vec3 start_pos)
	: Entity(world_ptr)
{
	type = EntityType::SHIP;

	move_speed = GameModule::resources->GetFloatParameter("ship_move_speed");
}

Ship::~Ship()
{
}

void Ship::Update()
{
	
	transform_mat = physic_body->GetTransformMatrix();
	
	if (GameModule::input->GetKeyState(SDL_SCANCODE_LEFT)
		|| GameModule::input->GetKeyState(SDL_SCANCODE_A))
	{
		physic_body->body->activate(true);

		btVector3 impulse(0.0f, 0.0f, move_speed);
		physic_body->body->applyCentralImpulse(impulse);
	}
	else if (GameModule::input->GetKeyState(SDL_SCANCODE_RIGHT)
		|| GameModule::input->GetKeyState(SDL_SCANCODE_D))
	{
		physic_body->body->activate(true);

		btVector3 impulse(0.0f, 0.0f, -move_speed);
		physic_body->body->applyCentralImpulse(impulse);
	}
	
}

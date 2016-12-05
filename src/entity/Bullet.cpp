#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<btDiscreteDynamicsWorld> world_ptr,
	glm::vec3 start_pos, glm::vec3 scale)
	: Entity(world_ptr, start_pos, scale)
{
	type = EntityType::BULLET;
	mesh = GameModule::resources->GetMesh("cube");
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	physic_body = std::make_unique<PhysicBody>(world.lock(), pos, scale, type, shared_from_this());

	//2d movement
	physic_body->body->setLinearFactor(btVector3(1, 0, 1));

	float move_speed = GameModule::resources->GetFloatParameter("bullet_move_speed");
	btVector3 velocity(-move_speed, 0.0f, 0.0f);
	physic_body->body->setLinearVelocity(velocity);

	//to avoid render on start in world center
	transform_mat = physic_body->GetTransformMatrix();
}

void Bullet::Update()
{
	transform_mat = physic_body->GetTransformMatrix();

	btTransform transform;
	physic_body->body->getMotionState()->getWorldTransform(transform);
	float pos_x = transform.getOrigin().getX();

	if (pos_x < -100.0f)
		Destroy();
}
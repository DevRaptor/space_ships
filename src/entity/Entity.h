#pragma once


class Entity
{
public:
	Entity() { }
	virtual ~Entity() { }

	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:

	//model, shader handle
};

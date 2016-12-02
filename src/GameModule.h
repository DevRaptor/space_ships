#pragma once

#include <memory>

#include "Input.h"
#include "ResourceManager.h"

class GameModule
{
public:
	static Input input;
	static std::shared_ptr<ResourceManager> resources;

	static void Init();
};
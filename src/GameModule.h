#pragma once

#include <memory>

#include "Input.h"
#include "ResourceManager.h"

class GameModule
{
public:
	static std::shared_ptr<Input> input;
	static std::shared_ptr<ResourceManager> resources;

	static void Init();
};
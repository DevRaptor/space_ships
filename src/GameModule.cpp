#include "GameModule.h"

std::shared_ptr<Input> GameModule::input;
std::shared_ptr<ResourceManager> GameModule::resources;

void GameModule::Init()
{
	input = std::make_shared<Input>();
	resources = std::make_shared<ResourceManager>();
}
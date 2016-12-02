#include "GameModule.h"

Input GameModule::input;
std::shared_ptr<ResourceManager> GameModule::resources;

void GameModule::Init()
{
	resources = std::make_shared<ResourceManager>();
}
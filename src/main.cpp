#include <iostream>

#include "utility/Log.h"
#include "GameEngine.h"


int main(int argc, char* argv[])
{
	Logger::InitLog();

	GameEngine engine;

	while (!engine.IsExit())
	{
		engine.Update();
	}

	Logger::CloseLog();

	return 0;
}
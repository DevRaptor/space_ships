#include <iostream>

#include "GameEngine.h"

//SDL need undef main
#undef main

int main()
{
	GameEngine engine;

	while (!engine.IsExit())
	{
		engine.Update();
	}

	return 0;
}
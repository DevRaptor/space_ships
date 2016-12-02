#include "GameEngine.h"

#include <ctime>
#include <cstdlib>
#include <chrono>

#include "GameModule.h"
#include "utility/Log.h"

using namespace std::chrono_literals;

//fixed time step, 1 / 60 [s] = 16 ms
constexpr std::chrono::nanoseconds time_step(16ms);

GameEngine::GameEngine()
	: lag(0ns), time_start(Clock::now())
{
	Logger::InitLog();
	Logger::Log("===================================\n");
	Logger::Log("============Space Ships============\n");
	Logger::Log("===================================\n");

	std::time_t actual_date = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	Logger::Log("Start date: ", std::ctime(&actual_date), "\n");


	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		Logger::Log("Init SDL\n");
	}
	else
	{
		Logger::Log("Cannot init SDL!\n");
		std::exit(EXIT_FAILURE);
	}

	Logger::Log("Platform: ", SDL_GetPlatform(), "\n");

	renderer = std::make_shared<Renderer>(resolution_x, resolution_y);



	state = std::make_unique<GameState>();

}

GameEngine::~GameEngine()
{
	renderer.reset(); //close context and window before SDL_Quit()
	SDL_Quit();

	Logger::Log("===================================\n");
	Logger::Log("Close game\n");

	Logger::CloseLog();
}

void GameEngine::Update()
{
	HandleEvents();

	auto delta_time = Clock::now() - time_start;
	time_start = Clock::now();

	lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

	//fixed time step update
	while (lag >= time_step)
	{
		lag -= time_step;

		state->Update(time_step);
	}

	GameModule::input.Update();
	if (GameModule::input.GetKeyState(SDL_SCANCODE_ESCAPE))
		exit = true;

}

void GameEngine::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit = true;
	}
}


#include "GameEngine.h"

#include <chrono>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "utility\Log.h"

using namespace std::chrono_literals;

//fixed time step, 1 / 60 [s] = 16 ms
constexpr std::chrono::nanoseconds time_step(16ms);

GameEngine::GameEngine()
	: lag(0ns), time_start(Clock::now())
{
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


	window = SDL_CreateWindow("Space ships", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		resolution_x, resolution_y, SDL_WINDOW_OPENGL);
	
	if (window == NULL)
	{
		Logger::Log("Could not create window: ", SDL_GetError(), "\n");
		std::exit(EXIT_FAILURE);
	}


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	context = SDL_GL_CreateContext(window);

	SDL_GL_MakeCurrent(window, context);
	SDL_GL_SetSwapInterval(0);

	int gl_major, gl_minor;
	glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
	glGetIntegerv(GL_MINOR_VERSION, &gl_minor);
	Logger::Log("Video driver: ", SDL_GetCurrentVideoDriver(), "\n");
	Logger::Log("GL context version: ", gl_major, ".", gl_minor, "\n");

	//Init GLEW
	glewExperimental = true;
	glewInit();

	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0, 0, 0, 0);
	glViewport(0, 0, resolution_x, resolution_y);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

	state = std::make_unique<GameState>();

}

GameEngine::~GameEngine()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
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


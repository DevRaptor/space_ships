#include "Renderer.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "utility/Log.h"

Renderer::Renderer(int resolution_x, int resolution_y)
{
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
}

Renderer::~Renderer()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void Renderer::Render()
{

}
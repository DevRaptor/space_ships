#pragma once

#include <memory>

#include <SDL.h>

#define GLEW_STATIC //needed to static link GLEW

class Renderer
{
public:
	Renderer(int resolution_x, int resolution_y);
	~Renderer();

protected:
	SDL_Window* window;
	SDL_GLContext context;
};

#pragma once

#include <memory>


#define GLEW_STATIC //needed to static link GLEW
#include <GL/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include "rendering/Mesh.h"
#include "rendering/ShaderProgram.h"



class Renderer
{
public:
	Renderer(int resolution_x, int resolution_y);
	~Renderer();

	void Render();

protected:
	SDL_Window* window;
	SDL_GLContext context;

	std::shared_ptr<ShaderProgram> shader_program;
	std::shared_ptr<Mesh> mesh;

	GLuint vertex_buffer;
	GLuint color_buffer;
	glm::mat4 mvp;
	GLuint mvp_uniform;
};

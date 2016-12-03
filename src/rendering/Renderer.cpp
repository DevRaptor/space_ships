#include "Renderer.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameModule.h"
#include "utility/Log.h"

Renderer::Renderer(int resolution_x, int resolution_y)
{
	window = SDL_CreateWindow(GameModule::resources->GetStringParameter("game_title").c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
	SDL_GL_SetSwapInterval(GameModule::resources->GetIntParameter("vsync"));

	int gl_major, gl_minor;
	glGetIntegerv(GL_MAJOR_VERSION, &gl_major);
	glGetIntegerv(GL_MINOR_VERSION, &gl_minor);
	Logger::Log("Video driver: ", SDL_GetCurrentVideoDriver(), "\n");
	Logger::Log("GL context version: ", gl_major, ".", gl_minor, "\n");

	//Init GLEW
	glewExperimental = true;
	glewInit();

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0, 0, 0.5f, 0);
	glViewport(0, 0, resolution_x, resolution_y);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

	GLuint vertex_array;
	glGenVertexArrays(1, &vertex_array);
	glBindVertexArray(vertex_array);

	shader_program = std::make_shared<ShaderProgram>("data/shaders/color.vert", "data/shaders/color.frag");

	shader_program->UseProgram();

	mvp_uniform = glGetUniformLocation(shader_program->GetProgram(), "mvp");

	float ratio = static_cast<float>(resolution_x) / static_cast<float>(resolution_y);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f);

	glm::mat4 view = glm::lookAt(
		glm::vec3(4, 3, 3),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));

	glm::mat4 model = glm::mat4(1.0f);

	mvp = projection * view * model;


	//Triangle
	static const GLfloat vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
}

Renderer::~Renderer()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void Renderer::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	shader_program->UseProgram();

	glUniformMatrix4fv(mvp_uniform, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	SDL_GL_SwapWindow(window);

}
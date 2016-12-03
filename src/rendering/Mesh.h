#pragma once

#define GLEW_STATIC //needed to static link GLEW
#include <GL/glew.h>

class Mesh
{
public:
	Mesh();
	~Mesh();

	void Draw();

private:
	int vertex_amount;

	GLuint vao;
	GLuint vbo_vertex;
	GLuint vbo_color;
};

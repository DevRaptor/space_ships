#pragma once

#include <string>

#define GLEW_STATIC //needed to static link GLEW
#include <GL/glew.h>
#include <glm/glm.hpp>


class ShaderProgram
{
public:
	ShaderProgram(const std::string& vert_path, const std::string& frag_path);
	~ShaderProgram();

	void UseProgram();
	GLuint GetProgram() { return program; }

private:
	GLuint program;

	void LoadFile(const std::string& file_name, std::string& buffer);

};


#include "ShaderProgram.h"

#include <vector>

#include "utility/Log.h"


ShaderProgram::ShaderProgram(const std::string& vert_path, const std::string& frag_path)
{
	GLuint vert_shader, frag_shader;
	std::string vert_buffer, frag_buffer;
	
	glUseProgram(0);
	program = glCreateProgram();

	LoadFile(vert_path, vert_buffer);
	vert_shader = glCreateShader(GL_VERTEX_SHADER);
	const char* vert_code = vert_buffer.c_str();
	glShaderSource(vert_shader, 1, &vert_code, nullptr);
	glCompileShader(vert_shader);
	glAttachShader(program, vert_shader);

	LoadFile(frag_path, frag_buffer);
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* frag_code = frag_buffer.c_str();
	glShaderSource(frag_shader, 1, &frag_code, nullptr);
	glCompileShader(frag_shader);
	glAttachShader(program, frag_shader);

	glLinkProgram(program);

	
	GLint result = GL_FALSE;
	int info_length;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length);
	if (info_length > 0) 
	{
		std::vector<char> error_message(info_length + 1);
		glGetProgramInfoLog(program, info_length, NULL, &error_message[0]);
		Logger::Log("Shader program error: ", std::string(&error_message[0]));
	}

	//clean
	glDetachShader(program, vert_shader);
	glDetachShader(program, frag_shader);

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::UseProgram()
{
	glUseProgram(program);
}


void ShaderProgram::LoadFile(const std::string& file_name, std::string& buffer)
{
	std::ifstream file(file_name);
	if (!file.is_open())
	{
		Logger::Log("Cannot open shader file: ", file_name, "\n");
		return;
	}

	file.seekg(0, std::ios::end);
	buffer.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	buffer.assign((std::istreambuf_iterator<char>(file)), 
		(std::istreambuf_iterator<char>()));

	file.close();
}
#include <fstream>
#include <string>
#include "comm.hpp"
#include "ShaderProgram.hpp"

static std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	throw(errno);
}


ShaderProgram::ShaderProgram() {
	ID = glCreateProgram();
}

ShaderProgram& ShaderProgram::AttachShader(const char *filename,GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);
	std::string tmp = get_file_contents(filename);
	const char *src = tmp.c_str();
	glShaderSource(shader,1,&src,NULL);
	glCompileShader(shader);
	shaders.push_back(shader);
	glAttachShader(ID, shader);
	return *this;
}

ShaderProgram& ShaderProgram::Link() {
	glLinkProgram(ID);
	for (auto shader : shaders) {
		glDeleteShader(shader);
	}
	return *this;
}

ShaderProgram& ShaderProgram::Use() {
	glUseProgram(ID);
	return *this;
}

void ShaderProgram::Delete() {
	glDeleteProgram(ID);
}

ShaderProgram& ShaderProgram::Uniform1i(const char* key, GLuint value)
{
	// Gets the location of the uniform
	GLuint uni = glGetUniformLocation(ID, key);
	glUniform1i(uni, value);
	return *this;
}

ShaderProgram & ShaderProgram::UniformMatrix4fv(const char * key, GLfloat * value)
{
	GLuint uni = glGetUniformLocation(ID, key);
	glUniformMatrix4fv(uni, 1, GL_FALSE, value);
	return *this;
}

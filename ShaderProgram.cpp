#include <fstream>
#include <string>
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

void ShaderProgram::Link() {
	glLinkProgram(ID);
	for (auto shader : shaders) {
		glDeleteShader(shader);
	}
}

void ShaderProgram::Use() {
	glUseProgram(ID);
}

void ShaderProgram::Delete() {
	glDeleteProgram(ID);
}
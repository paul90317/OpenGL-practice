#ifndef __SHADER_PROGRAM_HPP
#define __SHADER_PROGRAM_HPP

#include <vector>
#include "comm.hpp"

class ShaderProgram{
public:
	ShaderProgram();
	ShaderProgram& Use();
	void Delete();
	ShaderProgram& AttachShader(const char*,GLenum);
	ShaderProgram& Uniform1i(const char* key, GLuint value);
	ShaderProgram& UniformMatrix4fv(const char* key, GLfloat *value);
	ShaderProgram& Link();
	GLuint ID;
private:
	std::vector<GLuint> shaders;
};

#endif
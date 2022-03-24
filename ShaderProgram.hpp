#ifndef __SHADER_PROGRAM_HPP
#define __SHADER_PROGRAM_HPP

#include <vector>
#include "comm.hpp"

class ShaderProgram{
public:
	ShaderProgram();
	void Use();
	void Delete();
	ShaderProgram& AttachShader(const char*,GLenum);
	void Link();
private:
	std::vector<GLuint> shaders;
	GLuint ID;
};

#endif
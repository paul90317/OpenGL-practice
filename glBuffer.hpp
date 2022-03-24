#ifndef __GL_BUFFER_H
#define __GL_BUFFER_H
#include "comm.hpp"

class glBuffer {
private:
	GLuint ID;
	GLenum BIND_TARGET;
public:
	glBuffer(void*, size_t, GLenum, GLenum);
	void UnBind();
	void Delete();
};

#endif // !__GL_BUFFER_H



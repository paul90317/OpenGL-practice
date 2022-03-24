#ifndef __GL_BUFFER_H
#define __GL_BUFFER_H
#include "comm.hpp"
#include "glObject.hpp"

class glBuffer : public glObject {
private:
	GLuint ID;
	GLenum BIND_TARGET;
public:
	glBuffer(void*, size_t, GLenum, GLenum);
	void UnBind();
	void Delete();
	void Bind();
};

#endif // !__GL_BUFFER_H



#ifndef __VERTEX_ARRAY_H
#define __VERTEX_ARRAY_H
#include "comm.hpp"
#include "glBuffer.hpp"
#include <vector>

#define addBuf(values,bindTarget,usage) AddBuffer(glBuffer(values, sizeof(values), bindTarget, usage))


class VertexArray
{
private:
	GLuint ID;
	std::vector<glBuffer> bufs;
public:
	VertexArray();
	void Attrib(GLuint, GLuint, GLenum, GLsizei);
	VertexArray &AddBuffer(glBuffer buf);
	void UnBindAll();
	void Bind();
	void Delete();
};
#endif


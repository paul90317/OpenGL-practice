#ifndef __VERTEX_ARRAY_H
#define __VERTEX_ARRAY_H
#include "comm.hpp"
#include "glBuffer.hpp"
#include <vector>

#define addBuf(values,bindTarget,usage) Add(glBuffer(values, sizeof(values), bindTarget, usage))


class VertexArray
{
private:
	GLuint ID;
	std::vector<glObject> bufs;
public:
	VertexArray();
	VertexArray &Attrib(GLuint layout, GLuint numComponents, GLenum dataType, GLsizeiptr stride,void* offset=0);
	VertexArray &Add(glObject buf);
	void UnBindAll();
	void Bind();
	void Delete();
};
#endif


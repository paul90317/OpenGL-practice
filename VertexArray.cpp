#include "VertexArray.hpp"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}
void VertexArray::Attrib(GLuint start, GLuint count, GLenum dataType, GLsizei stride) {
	glVertexAttribPointer(start, count, dataType, GL_FALSE, stride, NULL);
	glEnableVertexAttribArray(0);
}
void VertexArray::UnBindAll(){
	glBindVertexArray(0);
	for (auto buf : bufs) {
		buf.UnBind();
	}
}
void VertexArray::Bind() {
	glBindVertexArray(ID);
}
void VertexArray::Delete() {
	glDeleteBuffers(1, &ID);
	for (auto buf : bufs) {
		buf.Delete();
	}
}
VertexArray &VertexArray::AddBuffer(glBuffer buf) {
	bufs.push_back(buf);
	return *this;
}
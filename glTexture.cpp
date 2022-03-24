#include "glTexture.hpp"
#include <stb/stb_image.hpp>

glTexture::glTexture(GLenum bindTarget):
	BIND_TARGET(bindTarget)
{
	glGenTextures(1, &ID);
	glBindTexture(BIND_TARGET, ID);
}

void glTexture::UnBind()
{
	glBindTexture(BIND_TARGET, 0);
}

void glTexture::Delete()
{
	glDeleteTextures(1, &ID);
}

void glTexture::Bind()
{
	glBindTexture(BIND_TARGET, ID);
}

glTexture & glTexture::Generate(const char * filename)
{
	stbi_set_flip_vertically_on_load(true);
	unsigned char *bytes = stbi_load(filename, &widthImg, &heightImg, &numColCh, 0);
	glTexImage2D(BIND_TARGET, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	stbi_image_free(bytes);
	glGenerateMipmap(BIND_TARGET);
	return *this;
}

glTexture & glTexture::Parameteri(GLenum key, GLenum value)
{
	glTexParameteri(BIND_TARGET, key, value);
	return *this;
}

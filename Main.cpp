#include "comm.hpp"
#include "VertexArray.hpp"
#include "ShaderProgram.hpp"
#include "glTexture.hpp"
#include <stb/stb_image.hpp>

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	/****
	* 0  1
	* 2  3
	****/
	GLfloat vertices[] = 
	{ //   COORDINATES      /     COLORS            //
		-1.0f,  1.0f, 0.0f,     0.8f, 0.3f,  0.02f,  0,1,// 
		 1.0f,  1.0f, 0.0f,     0.8f, 0.3f,  0.02f,  1,1,// 
		-1.0f, -1.0f, 0.0f,     1.0f, 0.6f,  0.32f,  0,0,// 
		 1.0f, -1.0f, 0.0f,     0.9f, 0.45f, 0.17f,  1,0 // 
	};
	GLuint indices[] = 
	{
		0, 1, 3, // 
		0, 2, 3, // 
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "Hello Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Fail to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, 800, 800);
	
	ShaderProgram shaderProgram;
	shaderProgram
		.AttachShader("fragmentShader.glsl", GL_FRAGMENT_SHADER)
		.AttachShader("vertexShader.glsl", GL_VERTEX_SHADER)
		.Link();

	VertexArray VAO;
	VAO
		.addBuf(indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)
		.addBuf(vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW)
		.Add(glTexture(GL_TEXTURE_2D)
			.Parameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
			.Parameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST)
			.Parameteri(GL_TEXTURE_WRAP_S, GL_REPEAT)
			.Parameteri(GL_TEXTURE_WRAP_T, GL_REPEAT)
			.Generate("pop_cat.png"))
		.Attrib(0, 3, GL_FLOAT, 8 * sizeof(float))
		.Attrib(1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)))
		.Attrib(2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		

	VAO.UnBindAll();
	shaderProgram.Use();
	VAO.Bind();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, NULL);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
#include "comm.hpp"
#include "VertexArray.hpp"
#include "ShaderProgram.hpp"

int main_in_tri() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	/****
	*    2
	*	3 5
	*  0 4 1
	**/
	GLfloat vertices[] = {
		-0.5f,-0.5f *(float)sqrt(3)/3,0.0f, //0
		0.5f,-0.5f*(float)sqrt(3)/3,0.0f,   //1
		0.0f,(float)sqrt(3)/3,0.0f,         //2
		-0.25f,0.25f*(float)sqrt(3)/3,0.0f,  //3
		0.0f,-0.5f*(float)sqrt(3)/3,0.0f,   //4
		0.25f,0.25f*(float)sqrt(3)/3,0.0f,   //5
	};
	GLuint indices[] = {
		3,5,2,
		0,4,3,
		4,1,5
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
	shaderProgram.Use();

	VertexArray VAO;
	VAO
		.addBuf(vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW)
		.addBuf(indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW)
		.Attrib(0, 3, GL_FLOAT, sizeof(float) * 3);

	VAO.UnBindAll();
	VAO.Bind();

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, NULL);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {
		//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, NULL);
		//glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
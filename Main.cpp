#include "comm.hpp"
#include "VertexArray.hpp"
#include "ShaderProgram.hpp"
#include "glTexture.hpp"

int width = 800;
int height = 800;

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
		-0.5f,  0.5f, 0.0f,     0.8f, 0.3f, 0.02f,		0.0f,1.0f,// 
		 0.5f,  0.5f, 0.0f,     0.8f, 0.3f, 0.02f,		1.0f,1.0f,// 
		-0.5f, -0.5f, 0.0f,     1.0f, 0.6f, 0.32f,		0.0f,0.0f,// 
		 0.5f, -0.5f, 0.0f,     0.9f, 0.45f, 0.17f,		1.0f,0.0f // 
	};
	GLuint indices[] = 
	{
		0, 1, 3, // 
		0, 2, 3, // 
	};

	GLFWwindow* window = glfwCreateWindow(width, height, "Hello Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Fail to create GLFW window\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, width, height);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
	proj = glm::perspective(glm::radians(4000.0f), (float)(width/height), 0.1f, 100.0f);

	ShaderProgram shaderProgram;
	shaderProgram
		.AttachShader("fragmentShader.glsl", GL_FRAGMENT_SHADER)
		.AttachShader("vertexShader.glsl", GL_VERTEX_SHADER)
		.Link().Use()
		.Uniform1i("tex0", 0)
		.UniformMatrix4fv("model", glm::value_ptr(model))
		.UniformMatrix4fv("view", glm::value_ptr(view))
		.UniformMatrix4fv("proj", glm::value_ptr(proj));

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
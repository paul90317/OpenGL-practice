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
	{ //     COORDINATES     /        COLORS        /   TexCoord  //
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
	};
	GLuint indices[] = 
	{
		0, 1, 4,
		1, 2, 4,
		0, 1, 2,
		0, 2, 3,
		
		2, 3, 4,
		3, 0, 4
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
	proj = glm::perspective(45.0f, (float)(width/height), 0.1f, 100.0f);
	

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
		

	//VAO.UnBindAll();
	VAO.Bind();
	glEnable(GL_DEPTH_TEST);

	double prevTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double crntTime = glfwGetTime();
		if (crntTime - prevTime > 0.01f) {
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			model = glm::rotate(model, glm::radians((float)(50.0f)), glm::vec3(0.0f, 1.0f, 0.0f));

			shaderProgram
				.UniformMatrix4fv("model", glm::value_ptr(model));

			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, NULL);
			glfwSwapBuffers(window);
			prevTime = crntTime;
		}
		
		glfwPollEvents();
	}

	VAO.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
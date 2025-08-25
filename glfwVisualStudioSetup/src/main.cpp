#define GLFW_INCLUDE_NONE
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <openglErrorReporting.h>
#include <shader.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "stb_image/stb_image.h"

float vertices[] = {
	// position         // color           // tex coord
	 0.5f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f    // top left
};

unsigned short indices[] =
{
	0, 1, 2,
	0, 2, 3
};

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init Error!\n";
		return 1;
	}

	GLFWwindow *window = glfwCreateWindow(640, 480, "First Window", NULL, NULL);
	if (!window)
	{
		std::cout << "Window Error!/n";
		return 1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return 1;
	}

	enableReportGlErrors();

#pragma region Loading Texture

	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("resources/assets/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// Texture 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("resources/assets/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

#pragma endregion

#pragma region imgui
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
#pragma endregion

#pragma region VAO

	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

#pragma endregion

#pragma region buffer

	GLuint buffer = 0;
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position Vertex Array
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);

	// Color Vertex Array
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(sizeof(float) * 3));

	// Texture Vertex Array
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));

#pragma endregion

#pragma region Indices

	GLuint indexBuffer = 0;
	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#pragma endregion

#pragma region Unbind VAO

	glBindVertexArray(0);

#pragma endregion

#pragma region Shaders
	
	Shader shader;

	shader.loadShaderProgramFromFile("resources/Shader.vert", "resources/Shader.frag");
	shader.bind();

	//GLuint u_time = shader.GetUniformLocation("u_time");
	GLuint u_color = shader.GetUniformLocation("u_color");
	GLuint u_texture1 = shader.GetUniformLocation("u_texture1");
	GLuint u_texture2 = shader.GetUniformLocation("u_texture2");
	GLuint u_transform = shader.GetUniformLocation("u_transform");

#pragma endregion


	while (!glfwWindowShouldClose(window))
	{
		int w = 0, h = 0;
		glfwGetWindowSize(window, &w, &h);
		glViewport(0, 0, w, h);

		glClear(GL_COLOR_BUFFER_BIT);

#pragma region ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
#pragma endregion

		// Window for color picker
		ImGui::Begin("Window");
		ImGui::Text("Color Test");
		static float color[3] = { 0.5, 0.5, 0.5 };
		ImGui::ColorPicker3("Color: ", color);
		//ImGui::ShowDemoWindow();
		ImGui::End();

		shader.bind();
		glUniform1i(u_texture1, 0);
		glUniform1i(u_texture2, 1);

		glUniform3fv(u_color, 1, color);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);

		glm::mat4 transform1 = glm::mat4(1.0f);
		transform1 = glm::translate(transform1, glm::vec3(0.5f, -0.5f, 0.0f));
		transform1 = glm::rotate(transform1, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(transform1));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);


		glm::mat4 transform2 = glm::mat4(1.0f);
		transform2 = glm::translate(transform2, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scale = sin(glfwGetTime());
		transform2 = glm::scale(transform2, glm::vec3(scale, scale, scale));
		glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(transform2));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

#pragma region ImGui
		ImGui::Render();
		int displayWidth = 0, diaplayHeight = 0;
		glfwGetFramebufferSize(window, &displayWidth, &diaplayHeight);
		glViewport(0, 0, displayWidth, diaplayHeight);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#pragma endregion


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &buffer);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
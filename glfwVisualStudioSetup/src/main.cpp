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
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
unsigned short indices[] =
{
	0, 1, 2,
	0, 2, 3
};

glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 LightPos = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 LightFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 LightUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool firstMouse = true;
float lastX = 400;
float lastY = 300;
float sensivity = 0.1f;

float yaw = 0;
float pitch = 0;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = (xpos - lastX) * sensivity;
	float yOffset = (lastY - ypos) * sensivity;
	lastX = xpos;
	lastY = ypos;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	CameraFront = glm::normalize(direction);
}

void processInput(GLFWwindow* window)
{
	const float cameraSpeed = 5.0f * deltaTime;
	const float lightMoveSpeed = 5.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		CameraPos += cameraSpeed * CameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		CameraPos -= cameraSpeed * CameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		CameraPos -= glm::normalize(glm::cross(CameraFront, CameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		CameraPos += glm::normalize(glm::cross(CameraFront, CameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		LightPos += lightMoveSpeed * LightFront;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		LightPos -= lightMoveSpeed * LightFront;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		LightPos -= glm::normalize(glm::cross(LightFront, LightUp)) * lightMoveSpeed;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		LightPos += glm::normalize(glm::cross(LightFront, LightUp)) * lightMoveSpeed;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		LightPos += LightUp * lightMoveSpeed;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		LightPos -= LightUp * lightMoveSpeed;
	if (glfwGetMouseButton(window, 1) == GLFW_PRESS)
		glfwSetCursorPosCallback(window, mouse_callback);
}

int main()
{
	if (!glfwInit())
	{
		std::cout << "GLFW Init Error!\n";
		return 1;
	}

	GLFWwindow *window = glfwCreateWindow(800, 600, "First Window", NULL, NULL);
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

	unsigned int diffuseMap, specularMap;
	glGenTextures(1, &diffuseMap);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("resources/assets/container2.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	// Texture 2
	glGenTextures(1, &specularMap);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("resources/assets/container2_specular.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum fmt = (nrChannels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
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

#pragma region buffer

	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint buffer = 0;
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position Vertex Array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal Vertex Array
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Vertex Array
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	GLuint lightVAO = 0;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

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

	//GLuint u_time = shader.GetUniformLocation("u_time");
	GLuint u_transform = shader.GetUniformLocation("u_transform");
	GLuint u_view = shader.GetUniformLocation("u_view");
	GLuint u_projection = shader.GetUniformLocation("u_projection");
	GLuint u_viewPos = shader.GetUniformLocation("u_viewPos");

	Shader lightShader;
	lightShader.loadShaderProgramFromFile("resources/LightShader.vert", "resources/LightShader.frag");
	
	GLuint u_lightColor = lightShader.GetUniformLocation("u_lightColor");
	GLuint u_lightTransform = lightShader.GetUniformLocation("u_lightTransform");
	GLuint u_lightView = lightShader.GetUniformLocation("u_lightView");
	GLuint u_lightProjection = lightShader.GetUniformLocation("u_lightProjection");

#pragma endregion

	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	glEnable(GL_DEPTH_TEST);
	
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	shader.bind();
	shader.SetInt("material.diffuse", 0);
	shader.SetInt("material.specular", 1);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		int w = 0, h = 0;
		glfwGetWindowSize(window, &w, &h);
		glViewport(0, 0, w, h);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		processInput(window);

#pragma region ImGui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// Window for color picker
		ImGui::Begin("Window");
		ImGui::Text("Color Test");
		static float color[3] = { 1.0f, 1.0f, 1.0f };
		ImGui::ColorPicker3("Color: ", color);

		ImGui::Text("Light Color Test");
		static float lightColor[3] = { 1.0f, 1.0f, 1.0f };
		ImGui::ColorPicker3("Light Color: ", lightColor);
		//ImGui::ShowDemoWindow();
		ImGui::End();
#pragma endregion

#pragma region Matrix

		// View Matrix
		glm::mat4 view;
		view = glm::lookAt(CameraPos, CameraPos + CameraFront, CameraUp);

		// Projection Matrix
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		glm::mat4 lightTransform = glm::mat4(1.0f);
		glm::vec3 lightPos(LightPos);

#pragma endregion

		// Transform Matrix
		shader.bind();
		glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));

		shader.SetVec3("u_viewPos", CameraPos);
		// Sending Material
		shader.SetFloat("material.shininess", 32.0f);

		// Sending Light
		shader.SetVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader.SetVec3("light.diffuse", glm::vec3(lightColor[0], lightColor[1], lightColor[2]));
		shader.SetVec3("light.specular", glm::vec3(lightColor[0], lightColor[1], lightColor[2]));
		shader.SetVec3("light.direction", glm::vec3(glm::normalize(-lightPos)));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, cubePositions[i]);
			glUniformMatrix4fv(u_transform, 1, GL_FALSE, glm::value_ptr(transform));
			float angle = 20.0f * i;
			transform = glm::rotate(transform, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		lightShader.bind();
		static float objectColor[3] = { 0.5, 0.5, 0.5 };
		glUniform3fv(u_lightColor, 1, lightColor);

		lightTransform = glm::translate(lightTransform, lightPos);
		lightTransform = glm::scale(lightTransform, glm::vec3(0.2f));
		glUniformMatrix4fv(u_lightTransform, 1, GL_FALSE, glm::value_ptr(lightTransform));
		glUniformMatrix4fv(u_lightView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(u_lightProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

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

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &buffer);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
#version 330 core
layout(location = 0) in vec4 aPos;
out vec4 vertexColor;

void main()
{
	gl_Position = aPos;
	vertexColor = vec4(1.0, 1.0, 1.0, 1.0); // Set vertex color to white
}
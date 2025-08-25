#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 in_texCoord;

out vec3 v_color;
out vec3 v_position;
out vec2 v_texCoord;

uniform mat4 u_transform;

void main()
{
	gl_Position = u_transform * vec4(in_position, 1);
	v_color = in_color;
	v_position = in_position;
	v_texCoord = in_texCoord;
}
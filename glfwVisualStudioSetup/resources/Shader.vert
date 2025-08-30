#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_texCoords;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_texCoords;

uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_transform * vec4(in_position, 1);
	v_position = vec3(u_transform * vec4(in_position, 1.0));
	v_normal = mat3(transpose(inverse(u_transform))) * in_normal;
	v_texCoords = in_texCoords;
}
#version 330 core

layout(location = 0) in vec3 in_position;

out vec3 v_position;

uniform mat4 u_transform;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position = u_projection * u_view * u_transform * vec4(in_position, 1);
	v_position = in_position;
}
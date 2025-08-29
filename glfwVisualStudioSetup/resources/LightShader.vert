#version 330 core

layout(location = 0) in vec3 in_position;

out vec3 v_position;

uniform mat4 u_lightTransform;
uniform mat4 u_lightView;
uniform mat4 u_lightProjection;

void main()
{
	gl_Position = u_lightProjection * u_lightView * u_lightTransform * vec4(in_position, 1);
	v_position = in_position;
}
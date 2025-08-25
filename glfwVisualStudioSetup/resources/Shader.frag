#version 330 core

layout(location = 0) out vec4 out_color;

in vec3 v_color;
in vec3 v_position;
in vec2 v_texCoord;

uniform vec3 u_color;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

void main()
{
	vec4 _textureColor = mix(texture(u_texture1, v_texCoord), texture(u_texture2, vec2(-v_texCoord.x, v_texCoord.y)), 0.2);
	out_color = _textureColor * vec4(u_color, 1);
}
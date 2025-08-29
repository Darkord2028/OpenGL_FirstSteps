#version 330 core

layout(location = 0) out vec4 out_color;

in vec3 v_position;
in vec3 v_normal;

uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

void main()
{
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(u_lightPos - v_position);

	float diff = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = diff * u_lightColor;
	
	float ambientStrength = 0.1;
	vec3 ambientColor = ambientStrength * u_lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(u_viewPos - v_position);
	vec3 reflectDir = reflect(-lightDirection, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * u_lightColor;

	vec3 finalColor = (ambientColor + diffuse + specular) * u_objectColor;
	out_color = vec4(finalColor, 1.0);
}
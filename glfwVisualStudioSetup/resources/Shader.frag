#version 330 core

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	//vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

layout(location = 0) out vec4 out_color;

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texCoords;

uniform vec3 u_viewPos;

uniform Material material;
uniform Light light;

void main()
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_texCoords));

	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(-light.direction);

	float diff = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_texCoords));

	vec3 viewDir = normalize(u_viewPos - v_position);
	vec3 reflectDir = reflect(-lightDirection, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, v_texCoords));

	vec3 finalColor = ambient + diffuse + specular;
	out_color = vec4(finalColor, 1.0);
}
#version 400

#define NUM_POINT_LIGHTS 4
#define SHADOWED

out vec4 frag_colour;
in vec3 pos;
in vec3 normal;
in vec2 uv;
uniform mat4 view;

#include("Materials.shx")

#include("PhongLights.shx")

/* MAIN */

void main() {

	Material mat;

	vec3 ambientTexture = texture(material.ambientTexture, uv).xyz;
	vec3 diffuseTexture = texture(material.diffuseTexture, uv).xyz;
	vec3 specularTexture = texture(material.specularTexture, uv).xyz;
	mat.ambient = material.ambient * ambientTexture;
	mat.diffuse = material.diffuse * diffuseTexture;
	mat.specular = material.specular * specularTexture;
	if (texture(material.diffuseTexture, uv).xyz == vec3(0.0)) { 
		mat.ambient = material.ambient;
		mat.diffuse = material.diffuse;
		mat.specular = material.specular;
	}

	mat.shininess = material.shininess;

	vec3 norm = normalize(normal);

	vec3 finalColor = vec3(0.0);

	finalColor += CalcDirLight(dirLight, norm, pos, view, mat);

	for(int i = 0; i < NUM_POINT_LIGHTS; i++) {
		finalColor += CalcPointLight(pointLight[i], norm, pos, view, mat);
	}

	frag_colour = vec4(finalColor, 1.0);
}
#version 400

#define NUM_POINT_LIGHTS 4
#define SHADOWED
#define BLINN_PHONG

out vec4 frag_colour;
in vec3 pos;
in vec3 normal;
in vec2 uv;
uniform mat4 view;

#include("Materials.shx")

#include("PhongLights.shx")

/* MAIN */

void main() {
	DirLight l;
	l.direction = vec3(-1.0, -3.0, -1.0);
	l.ambient = vec3(0.3);
	l.diffuse = vec3(0.8);
	l.specular = vec3(1.0);

	Material mat;
	mat.ambient = material.ambient + texture(textureMaterial.ambient, uv).xyz;
	mat.diffuse = material.diffuse + texture(textureMaterial.diffuse, uv).xyz;
	mat.specular = material.specular + texture(textureMaterial.specular, uv).xyz;

	vec3 norm = normalize(normal);

	vec3 finalColor = vec3(0.0);

	finalColor += CalcDirLight(dirLight, norm, pos, view, mat);

	for(int i = 0; i < NUM_POINT_LIGHTS; i++) {
		finalColor += CalcPointLight(pointLight[i], norm, pos, view, mat);
	}

	frag_colour = vec4(finalColor, 1.0);
}
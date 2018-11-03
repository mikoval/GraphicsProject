#version 400
layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uv_i;

out vec3 pos;
out vec3 normal;
out vec2 uv;
out vec4 FragPosLightSpace;


uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 inverse;
uniform mat4 lightSpace;
void main() {
	FragPosLightSpace = lightSpace * model * vec4(vp, 1.0);
	uv = uv_i;
	pos = (view * model * vec4(vp, 1.0)).xyz;
	normal = mat3(inverse) * norm;
	gl_Position = proj * view * model * vec4(vp, 1.0);
}
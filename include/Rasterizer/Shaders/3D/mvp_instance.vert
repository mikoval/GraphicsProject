#version 400
layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uv_i;
layout (location = 3) in mat4 model_i;

out vec3 pos;
out vec3 normal;
out vec2 uv;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform mat4 inverse;
void main() {
	uv = uv_i;
	mat4 final_model = model_i * model;
	mat4 vm = view * final_model;
   pos = (vm * vec4(vp, 1.0)).xyz;
	normal = mat3(vm) * norm;
	gl_Position = proj * vm * vec4(vp, 1.0);
}
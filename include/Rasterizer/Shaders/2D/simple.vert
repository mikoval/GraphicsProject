#version 400
layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 uv_i;

out vec2 uv;

void main() {
	uv = uv_i;
	gl_Position = vec4(vp, 1.0);
}
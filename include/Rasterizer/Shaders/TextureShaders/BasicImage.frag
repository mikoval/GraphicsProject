#version 400

out vec4 frag_colour;

in vec2 uv;

uniform sampler2D tex;

void main() {

	frag_colour = vec4(texture(tex, uv).xyz, 1.0);
}
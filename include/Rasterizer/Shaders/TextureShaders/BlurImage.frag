#version 400

out vec4 frag_colour;

in vec2 uv;

uniform sampler2D tex;
uniform vec2 res;

void main() {
	ivec2 coord = ivec2(uv * res);

	vec3 color = vec3(0.0);

	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			color += texelFetch(tex, coord + ivec2(i, j), 0).xyz;
		}
	}
	color /= 9.0;
	frag_colour = vec4(color, 1.0);
}
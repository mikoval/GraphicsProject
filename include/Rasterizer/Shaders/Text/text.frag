#version 330 core
in vec2 texcoord;
out vec4 out_color;
uniform vec4 color;
uniform sampler2D text_atlas;

void main(){
  out_color = vec4(1.0, 1.0, 1.0, texture(text_atlas, texcoord.xy).r);

}
#version 450

layout(location = 2) in vec2 frag_tex_coord;
layout(location = 0) out vec4 out_color;

layout(binding = 1) uniform sampler2D tex_sampler;


void main(){
  //---------------------------

  out_color = texture(tex_sampler, frag_tex_coord);
  //out_color = vec4(1,0,0,1);

  //---------------------------
}

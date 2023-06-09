#version 450

layout(location = 2) in vec2 frag_tex_coord;
layout(location = 0) out vec4 out_color;

layout(binding = 0) uniform sampler2D tex_color;


void main(){
  //---------------------------

  vec4 color = texture(tex_color, frag_tex_coord);
  out_color = vec4(color.y-0.5, color.z-0.5, color.x, color.w);

  //---------------------------
}

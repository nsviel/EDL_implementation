#version 450

layout(location = 2) in vec2 frag_tex_coord;
layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler2D tex_color;
layout(set = 0, binding = 1) uniform sampler2D tex_depth;
layout(set = 0, binding = 2) uniform sampler2D tex_position;


void main(){
  //---------------------------

  vec4 color = texture(tex_color, frag_tex_coord);
  vec4 depth = texture(tex_depth, frag_tex_coord);

  float d = depth.x;
  if(d <= 0.9999){
  out_color = vec4(1, 1, 1, color.w);
  }else{
  out_color = vec4(0);
  }


  //---------------------------
}

#version 450

layout(location = 0) in vec3 frag_position;
layout(location = 1) in vec3 frag_color;
layout(location = 0) out vec4 out_color;


void main(){
  //---------------------------

  //Position
  //out_position = vec4(frag_position, 1);

  //Color
  out_color = vec4(frag_color, 1);

  //---------------------------
}

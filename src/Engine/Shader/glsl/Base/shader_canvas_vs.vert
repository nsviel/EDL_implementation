#version 450

layout(location = 0) in vec3 in_position;
layout(location = 2) in vec2 in_tex_coord;
layout(location = 2) out vec2 frag_tex_coord;

layout(binding = 0) uniform MVP{
    mat4 mvp;
}ubo;


void main() {
  //---------------------------

  gl_Position = ubo.mvp * vec4(in_position, 1.0);
  frag_tex_coord = in_tex_coord;

  //---------------------------
}

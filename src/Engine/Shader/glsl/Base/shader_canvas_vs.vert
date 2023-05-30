#version 450

layout(location = 0) in vec3 in_position;
layout(location = 2) in vec2 in_tex_coord;
layout(location = 0) out vec4 out_color;
layout(location = 2) out vec2 frag_tex_coord;

layout(binding = 0) uniform MVP{
    mat4 mvp;
}ubo;

layout(push_constant) uniform constants{
  mat4 mvp;
}push;


void main() {
  //---------------------------

  gl_Position = push.mvp * vec4(in_position, 1.0);
  frag_tex_coord = in_tex_coord;

  //---------------------------
}

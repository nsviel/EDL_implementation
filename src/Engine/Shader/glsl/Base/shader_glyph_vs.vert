#version 450

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 0) out vec3 frag_color;

layout(binding = 0) uniform MVP{
    mat4 mvp;
}ubo;

layout(push_constant) uniform constants{
  mat4 mvp;
}push;


void main() {
  //---------------------------

  gl_Position = push.mvp * vec4(in_position, 1.0);
  gl_PointSize = 5.0;

  frag_color = in_color;

  //---------------------------
}

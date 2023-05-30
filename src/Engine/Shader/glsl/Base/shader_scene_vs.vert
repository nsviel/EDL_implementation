#version 450
#extension GL_EXT_debug_printf : enable

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 0) out vec3 frag_color;

layout(binding = 1) uniform MVP{
    mat4 mvp;
} ubo;


void main() {
  //---------------------------

  gl_Position = ubo.mvp * vec4(in_position, 1.0);
  gl_PointSize = 5.0;
  frag_color = in_color;

  float myfloat = 3.1415f;
  //debugPrintfEXT("My float is %f", gl_Position.x);

  //---------------------------
}

#version 450
#extension GL_EXT_debug_printf : enable

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 0) out vec3 frag_position;
layout(location = 1) out vec3 frag_color;

layout(binding = 0) uniform MVP{
    mat4 mvp;
}ubo_mvp;
layout(binding = 1) uniform SIZE{
    int point_size;
}ubo_size;
layout(push_constant) uniform PushConstants {
  mat4 mvp;
} push;


void main(){
  //---------------------------

  gl_Position = ubo_mvp.mvp * vec4(in_position, 1.0);
  gl_PointSize = ubo_size.point_size;
  frag_color = in_color;

  //---------------------------
}

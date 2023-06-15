#version 450
#extension GL_EXT_debug_printf : enable

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 0) out vec3 frag_color;

layout(set = 0, binding = 0) uniform MVP{
    mat4 mvp;
}ubo_mvp;
layout(set = 0, binding = 1) uniform SIZE{
    int point_size;
}ubo_size;


void main(){
  //---------------------------

  gl_Position = ubo_mvp.mvp * vec4(in_position, 1.0);
  gl_PointSize = 5.0;
  frag_color = in_color;

  //debugPrintfEXT("\nshader-> %d", ubo_size.point_size);
  debugPrintfEXT("\nshader-> %f", ubo_mvp.mvp[0][0]);

  //---------------------------
}

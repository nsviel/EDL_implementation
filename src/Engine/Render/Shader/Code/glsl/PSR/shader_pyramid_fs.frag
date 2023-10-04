#version 450
#define PI 3.1415926538
#extension GL_EXT_debug_printf : enable
//debugPrintfEXT("\n--> %f", shade);

layout(location = 2) in vec2 frag_tex_coord;
layout(location = 1) out vec4 out_position;

layout(binding = 0) uniform sampler2D tex_position;
layout(binding = 4) uniform sampler2D tex_depth;
layout(binding = 5) uniform param{
  float z_near;
  float z_far;
  int tex_width;
  int tex_height;
};


//FUNCTION 1 - Compute normalized depth
float compute_depth_normalized(float depth){
  //---------------------------

  float depth_norm = (2.0 * z_far * z_near) / ((z_far + z_near) - (2.0 * depth - 1.0) * (z_far - z_near));
  depth_norm = (depth_norm - z_near) / (z_far - z_near);
  depth_norm = clamp(depth_norm, 0.0, 1.0);

  //---------------------------
  return depth_norm;
}

void main(){
  //---------------------------

  //Depth
  float depth = texture(tex_depth, frag_tex_coord).r;
  float depth_norm = compute_depth_normalized(depth);
  vec2 offset = 0.5 / vec2(tex_width, tex_height);
  if(depth_norm < 0.99999999999){
    gl_FragDepth = depth;
    out_position = texture(tex_position, frag_tex_coord );
    out_position = vec4(frag_tex_coord,gl_FragDepth,1);
  }else{
    gl_FragDepth = 1;
    out_position = vec4(1, 1, 0, 1);
  }

  //---------------------------
}

#version 450
#define PI 3.1415926538

layout (location = 1) out vec4 out_position;

in vec2 vs_tex_coord;

uniform sampler2D tex_depth;
uniform sampler2D tex_position;

uniform float Z_NEAR;
uniform float Z_FAR;
uniform int GL_WIDTH;
uniform int GL_HEIGHT;
uniform mat4 VIEW;


//FUNCTION 1 - Compute normalized depth
float compute_depth_normalized(float depth){
  //---------------------------

  float depth_norm = (2.0 * z_far * z_near) / ((z_far + z_near) - (2.0 * depth - 1.0) * (z_far - z_near));
  depth_norm = (depth_norm - z_near) / (z_far - z_near);
  depth_norm = clamp(depth_norm, 0.0, 1.0);

  //---------------------------
  return depth_norm;
}


float compute_depth_normalized(float depth){
  //---------------------------

  float depth_norm = (2.0 * Z_NEAR) / (Z_FAR + Z_NEAR - depth * (Z_FAR - Z_NEAR));

  //---------------------------
  return depth_norm;
}

void main(){
  //---------------------------

  //Depth
  float depth = texture(tex_depth, vs_tex_coord).r;
  float depth_norm = compute_depth_normalized(depth);
  vec2 offset = 0.5 / vec2(GL_WIDTH, GL_HEIGHT);
  if(depth_norm < 0.99999999999){
    gl_FragDepth = depth;
    out_position = texture(tex_position, vs_tex_coord );
    out_position = vec4(vs_tex_coord,gl_FragDepth,1);
  }else{
    gl_FragDepth = 1;
    out_position = vec4(1, 1, 0, 1);
  }

  //---------------------------
}

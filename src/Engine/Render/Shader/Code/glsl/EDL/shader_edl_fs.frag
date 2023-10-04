#version 450

layout(location = 2) in vec2 frag_tex_coord;
layout(location = 0) out vec4 out_color;

layout(binding = 1) uniform sampler2D tex_color;
layout(binding = 4) uniform sampler2D tex_depth;
layout(binding = 5) uniform param{
  bool activated;
  float z_near;
  float z_far;
  float strength;
  float radius;
  int tex_width;
  int tex_height;
};

vec2 table_index[8] = vec2[](\
  vec2(1.0, 0.0),\
  vec2(1.0, 1.0),\
  vec2(0.0, 1.0),\
  vec2(-1.0, 1.0),\

  vec2(-1.0, 0.0),\
  vec2(-1.0, -1.0),\
  vec2(0.0, -1.0),\
  vec2(1.0, -1.0)\
);


//FUNCTION 1 - Compute normalized depth
float compute_depth_normalized(float depth){
  //---------------------------

  float depth_norm = (2.0 * z_far * z_near) / ((z_far + z_near) - (2.0 * depth - 1.0) * (z_far - z_near));
  depth_norm = (depth_norm - z_near) / (z_far - z_near);
  depth_norm = clamp(depth_norm, 0.0, 1.0);

  //---------------------------
  return depth_norm;
}

//FUNCTION 2 - Compute shading
float compute_shading(float depth_norm){
  //---------------------------

  vec2 texel_size = radius / vec2(tex_width, tex_height);
  vec2 max_dim = vec2(1.0 / tex_width, 1.0 / tex_height);

  //Shading according to all neighbors
  float sum = 0.0;
  for(int i=0; i<8; i++){
    vec2 offset = texel_size * table_index[i];
    vec2 NN_coord = frag_tex_coord + offset;

    //If to avoid border effect
    if(NN_coord.y < 1 && NN_coord.y > 0){
      vec4 depth_NN_rgba = texture(tex_depth, NN_coord);
      float depth_NN_norm = compute_depth_normalized(depth_NN_rgba.r);

      //Shading mode
      float diff_depth = log2(depth_norm) - log2(depth_NN_norm);

      sum +=  max(0.0, diff_depth);
    }
  }
  float shade = exp(-sum * strength);

  //---------------------------
  return shade;
}

//MAIN FUNCTION
void main(){
  //---------------------------
  vec4 color_rgba = texture(tex_color, frag_tex_coord);
  vec4 depth_rgba = texture(tex_depth, frag_tex_coord);
  float depth_norm = compute_depth_normalized(depth_rgba.r);

  if(depth_norm < 1 && activated){
    float shade = compute_shading(depth_norm);
    color_rgba.rgb *= shade;
  }

  //---------------------------
  out_color = vec4(color_rgba.rgb, 1.0);
}

#version 450

layout(location = 2) in vec2 frag_tex_coord;
layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler2D tex_color;
layout(set = 0, binding = 1) uniform sampler2D tex_depth;
layout(set = 0, binding = 2) uniform Params{
  float A;
  float B;
  float EDL_STRENGTH;
  float EDL_DISTANCE;
  float EDL_RADIUS;
  bool EDL_ON;
  int TEX_WIDTH;
  int TEX_HEIGHT;
};


//FUNCTION 1 - Compute normalized depth
float compute_depth_normalized(float depth){
  //---------------------------

  // depth: Linear depth, in world units
  // depth_norm: normalized depth between [0, 1]
  float depth_norm = 0.5 * (A * depth + B) / depth + 0.5;

  //---------------------------
  return depth_norm;
}

//FUNCTION 2 - Compute neighbor influence
vec2 neighbor_contribution(float depth_norm, vec2 offset){
  //---------------------------

  // get normalized depth at texture offseted coordinate
  vec2 NN_coord = frag_tex_coord + offset;
  vec4 depth_NN_rgba = texture(tex_depth, NN_coord);
  float depth_NN_norm = compute_depth_normalized(depth_NN_rgba.r);

  // interpolate the two adjacent depth values
  float NN_contrib = max(0.0, log2(depth_norm) - log2(depth_NN_norm));

  //---------------------------
  return vec2(NN_contrib, 1.0);
}

//MAIN FUNCTION
void main(){
  //---------------------------

  vec4 tex_color_rgba = texture(tex_color, frag_tex_coord);

  if(EDL_ON){
    // Build the Depth
    vec4 depth_rgba = texture(tex_depth, frag_tex_coord);
    float depth_norm = compute_depth_normalized(depth_rgba.r);

    //Check neighborhood influence
    vec2 texel_size = EDL_RADIUS / vec2(TEX_WIDTH, TEX_HEIGHT);
    vec2 NN_response = vec2(0.0);
    NN_response += neighbor_contribution(depth_norm, vec2(-texel_size.x, 0.0));
    NN_response += neighbor_contribution(depth_norm, vec2(+texel_size.x, 0.0));
    NN_response += neighbor_contribution(depth_norm, vec2(0.0, -texel_size.y));
    NN_response += neighbor_contribution(depth_norm, vec2(0.0, +texel_size.y));

    // Build the Eye Dome Lighting effect
    float depth_response = NN_response.x / NN_response.y;
    float shade = exp(-depth_response * 1500.0 * EDL_STRENGTH);

    tex_color_rgba.rgb *= shade;
  }

  //---------------------------
  out_color = vec4(tex_color_rgba);
}

#version 450

layout(location = 2) in vec2 frag_tex_coord;
layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler2D tex_color;
layout(set = 0, binding = 1) uniform sampler2D tex_depth;
layout(set = 0, binding = 2) uniform param{
  bool activated;
  float A;
  float B;
  float strength;
  float distance;
  float radius;
  int width;
  int height;
};


//FUNCTION 1 - Compute normalized depth
float compute_depth_normalized(float depth){
  // depth: Linear depth, in world units
  float depth_norm = 0.5 * (-A * depth + B) / depth + 0.5;
  // depth_norm: normalized depth between [0, 1]
  return depth_norm;
}

//FUNCTION 2 - Compute neighbor influence
vec2 neighbor_contribution(float depth_norm, vec2 offset) {
  // get depth at texture specified coordinate
  vec2 NN_coord = frag_tex_coord + offset;
  float depth_NN = texture(tex_depth, NN_coord).r;

  if (depth_NN == 0.0){
    return vec2(0.0);
  }

  // interpolate the two adjacent depth values
  float depth_NN_norm = compute_depth_normalized(depth_NN);
  float NN_contrib = max(0.0, log2(depth_norm) - log2(depth_NN_norm));

  return vec2(NN_contrib, 1.0);
}

//MAIN FUNCTION
void main()
{
  vec4 color = texture(tex_color, frag_tex_coord);

  if(activated){

    // Build the Depth
    float depth_buffer = texture(tex_depth, frag_tex_coord).r;
    float depth_norm = compute_depth_normalized(depth_buffer);

    //Check neighborhood influence
    vec2 texel_size = radius / vec2(width, height);
    vec2 NN_response = vec2(0.0);
    NN_response += neighbor_contribution(depth_norm, vec2(-texel_size.x, 0.0));
    NN_response += neighbor_contribution(depth_norm, vec2(+texel_size.x, 0.0));
    NN_response += neighbor_contribution(depth_norm, vec2(0.0, -texel_size.y));
    NN_response += neighbor_contribution(depth_norm, vec2(0.0, +texel_size.y));

    // Build the Eye Dome Lighting effect PostProcessing
    float depth_response = NN_response.x / NN_response.y;
    float shade = exp(-depth_response * 3000.0 * strength);

    color.rgb *= shade;

  }

  out_color = vec4(color);

}

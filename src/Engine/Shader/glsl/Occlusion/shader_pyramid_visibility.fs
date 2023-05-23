#version 400 core
#define PI 3.1415926538

layout (location = 0) out vec4 out_color;

in vec2 vs_tex_coord;

uniform sampler2D tex_depth;
uniform sampler2D tex_color;
uniform sampler2D tex_position;
uniform sampler2D tex_coord_0;
uniform sampler2D tex_coord_1;
uniform sampler2D tex_coord_2;
uniform sampler2D tex_coord_3;
uniform sampler2D tex_coord_4;

uniform int GL_WIDTH;
uniform int GL_HEIGHT;
uniform vec3 CAM_POSE;
uniform mat4 PROJ;
uniform mat4 VIEW;

const int index_size = 9;
float table_index[index_size] = float[](5.0, 4.0, 3.0, 6.0, -1.0, 2.0, 7.0, 0.0, 1.0);



float compute_norm(vec3 pos){
  //---------------------------

  float norm = sqrt(pow(pos.x, 2) + pow(pos.y, 2) + pow(pos.z, 2));

  //---------------------------
  return norm;
}
vec3 unproject(vec2 coord_tex){
  //---------------------------

  //Coord in Raster space to NDC coordinate
  vec2 coord_ndc;
  coord_ndc.x = (2 * coord_tex.x) - 1;
  coord_ndc.y = 1 - (2 * coord_tex.y);

  //Clip to view  space
  float depth = 0.99;
  float ratio = GL_WIDTH / GL_HEIGHT;
  vec4 coord_view;
  float fov_rad = 65 * (PI/180);
  coord_view.x = coord_ndc.x * tan(fov_rad / 2 ) * ratio;
  coord_view.y = coord_ndc.y * tan(fov_rad / 2 );
  coord_view.z = -0.001;
  coord_view.w = 1;

  vec3 fct_out  = vec3(coord_view);

  //---------------------------
  return fct_out;
}
vec4[9] compute_lvl_nn(int nn_size, sampler2D sampler_pos){
  vec4 nn_level[9];
  //---------------------------

  //Pixel coordinate information
  vec2 block_size = vec2(nn_size) / vec2(GL_WIDTH, GL_HEIGHT);
  vec2 offset = vec2(0.5) / vec2(GL_WIDTH, GL_HEIGHT);
  vec2 tex_coord_dim = vs_tex_coord * vec2(GL_WIDTH, GL_HEIGHT);

  //Retrieve all pixel neighbors
  int cpt = 0;
  for(int i=-1; i<2; i++){
    for(int j=-1; j<2; j++){
      vec2 cube_pos = (floor(tex_coord_dim / nn_size) * nn_size) / vec2(GL_WIDTH, GL_HEIGHT);

      vec2 block_coord = cube_pos + vec2(block_size.x * i, block_size.y * j) + offset;
      vec4 NN_coord = texture(sampler_pos, block_coord);

      float index = table_index[cpt];
      nn_level[cpt] = vec4(NN_coord.xyz, index);
      cpt ++;
    }
  }

  //---------------------------
  return nn_level;
}
bool compute_visibility(){
  //---------------------------

  //Get neighbor on all pyramid level
  vec4[9] nn_lvl_0 = compute_lvl_nn(1, tex_coord_0);
  vec4[9] nn_lvl_1 = compute_lvl_nn(2, tex_coord_1);
  vec4[9] nn_lvl_2 = compute_lvl_nn(4, tex_coord_2);
  vec4[9] nn_lvl_3 = compute_lvl_nn(8, tex_coord_3);
  vec4[9] nn_lvl_4 = compute_lvl_nn(16, tex_coord_4);

  //Concatenate the neighbor arrays
  vec4 sector[46];
  for(int i=0; i<9; i++){
    sector[i] = nn_lvl_0[i];
    sector[i+9] = nn_lvl_1[i];
    sector[i+18] = nn_lvl_2[i];
    sector[i+27] = nn_lvl_3[i];
    sector[i+36] = nn_lvl_4[i];
  }



  //Get X point in view space
  vec2 offset = 0.5 / vec2(GL_WIDTH, GL_HEIGHT);
  vec3 pixel_pos = texture(tex_position, vs_tex_coord).xyz;
  vec3 x =  pixel_pos;





  bool is_visible;


  //Compute X to cam vector
  vec3 pt_to_cam = - normalize(x);

  //for each sector and for each neighbor
  float nn_occlusion_sum = 0;
  for(int i=0; i<8; i++){
    //init variable by the highest value
    float sector_occlusion_min = 2;

    // Get minimal nn visibility per sector
    for(int j=0; j<46; j++){
      vec4 nn = sector[j];
      if(abs(i - nn.w) < 0.01 && nn.z < 0.01){
        vec2 nn_coord = nn.xy ;
        vec3 nn_pos = texture(tex_position, nn_coord).xyz;
        vec3 y = nn_pos;

        vec3 nn_cone = normalize(y - x);
        float nn_occlusion = 1 - dot(nn_cone, pt_to_cam);
        if(nn_occlusion < sector_occlusion_min){
          sector_occlusion_min = nn_occlusion;
        }
      }
    }

    //Get sum of all sector visibility
    nn_occlusion_sum += sector_occlusion_min;
  }
  float pixel_occ = nn_occlusion_sum / 8;


  if(pixel_occ < 0.005){
    is_visible = false;
  }else{
    is_visible = true;
  }


  //---------------------------
  return is_visible;
}

void main(){
  float depth = texture(tex_depth, vs_tex_coord).r;
  //---------------------------

  bool is_visible = false;
  vec4 color = vec4(1);

  if(depth < 0.99){
    is_visible = compute_visibility();

    if(is_visible){
      color = texture(tex_color, vs_tex_coord);
      //gl_FragDepth = texture(tex_depth, vs_tex_coord).r;
    //  color = vec4(1,0,0,1);
    }else{
      //color = vec4(0,0,1,0.5);
    }


  }

  //---------------------------
  out_color = color;
}

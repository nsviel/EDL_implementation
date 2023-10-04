#include "Glyphs.h"

#include "Base/Glyph_source.h"
#include "Scene/Grid.h"
#include "Scene/Axis_world.h"

#include "../Data_node.h"
#include "../Scene/Scene.h"

#include "../../Core/Core_node.h"
#include "../../Core/GPU/GPU_data.h"


//Constructor / Destructor
Glyphs::Glyphs(Data_node* data_node){
  //---------------------------

  Core_node* core_node = data_node->get_core_node();
  this->sceneManager = data_node->get_sceneManager();
  this->gpu_data = core_node->get_gpu_data();

  this->vec_glyph_src.push_back(new Grid());
  this->vec_glyph_src.push_back(new Axis_world());

  //---------------------------
}
Glyphs::~Glyphs(){
  //---------------------------

  for(int i=0; i<vec_glyph_src.size(); i++){
    delete vec_glyph_src[i];
  }

  //---------------------------
}

//Creation function
void Glyphs::create_glyph_scene(){
  //---------------------------

  for(int i=0; i<vec_glyph_src.size(); i++){
    vec_glyph_src[i]->create_glyph();
    Glyph* glyph = vec_glyph_src[i]->get_glyph();
    sceneManager->insert_glyph_object(glyph);
  }

  //---------------------------
}
Glyph_source* Glyphs::get_glyph_src_byName(string name){
  //---------------------------

  for(int i=0; i<vec_glyph_src.size(); i++){
    if(name == vec_glyph_src[i]->get_name()){
      return vec_glyph_src[i];
    }
  }

  //---------------------------
  return nullptr;
}


/*
//Main functions
void Glyphs::draw_glyph(Glyph* glyph){
  //---------------------------

  if(glyph->is_visible){
    gpuManager->draw_object(glyph);
  }

  //---------------------------
}
void Glyphs::insert_into_gpu(Glyph* glyph){
  //---------------------------

  gpuManager->gen_vao(glyph);
  gpuManager->gen_buffer_location(glyph);
  gpuManager->gen_buffer_color(glyph);
  gpuManager->convert_draw_type_byName(glyph);

  //---------------------------
}

//Glyph creation / supression
void Glyphs::create_glyph_scene(Glyph* glyph){
  Set* col_glyph = data->get_collection_byName("glyph", "glyph_scene");
  //---------------------------

  this->insert_into_gpu(glyph);
  col_glyph->obj_add_new(glyph);

  //---------------------------
}
void Glyphs::create_glyph_object(Object* object, Glyph* glyph){
  Set* col_glyph = data->get_collection_byName("glyph", "glyph_object");
  //---------------------------

  glyph->linked_object = cloud;
  this->insert_into_gpu(glyph);
  col_glyph->obj_add_new(glyph);

  //---------------------------
}
void Glyphs::remove_temporary_glyph(){
  Set* col_glyph = data->get_collection_byName("glyph", "glyph_scene");
  //---------------------------

  //Remove non permanent glyphs
  for(int i=0; i<col_glyph->list_obj.size(); i++){
    Glyph* glyph = (Glyph*)*next(col_glyph->list_obj.begin(),i);

    if(glyph->is_permanent == false){
      this->remove_glyph_scene(glyph->ID);
      i = 0;
    }
  }

  //---------------------------
}
void Glyphs::remove_glyph_scene(int ID){
  Set* col_glyph = data->get_collection_byName("glyph", "glyph_scene");
  //---------------------------

  for(int i=0;i<col_glyph->list_obj.size();i++){
    Glyph* glyph = (Glyph*)*next(col_glyph->list_obj.begin(),i);

    if(glyph->ID == ID){
      delete glyph;
      list<Object_*>::iterator it = next(col_glyph->list_obj.begin(), i);
      col_glyph->list_obj.erase(it);
    }
  }

  //---------------------------
}
Glyph* Glyphs::create_glyph(vector<vec3>& XYZ, vector<vec4>& RGB, string mode, bool perma){
  Set* col_glyph = data->get_collection_byName("glyph", "glyph_scene");
  Glyph* glyph = new Glyph();
  unsigned int VAO;
  uint colorVBO, locationVBO;
  //---------------------------

  glyph->xyz = XYZ;
  glyph->rgb = RGB;
  glyph->name = "...";
  glyph->draw_type_name = mode;
  glyph->draw_line_width = 1;
  glyph->is_permanent = perma;

  this->insert_into_gpu(glyph);
  col_glyph->list_obj.push_back(glyph);

  //---------------------------
  return glyph;
}

//Glyph update
void Glyphs::update_glyph_buffer(Glyph* glyph){
  //---------------------------

  gpuManager->update_buffer_location(glyph);
  gpuManager->update_buffer_color(glyph);

  //---------------------------
}
void Glyphs::update_glyph_location(Glyph* glyph){
  //---------------------------

  gpuManager->update_buffer_location(glyph);

  //---------------------------
}
void Glyphs::update_glyph_color(Glyph* glyph){
  //---------------------------

  gpuManager->update_buffer_color(glyph);

  //---------------------------
}
void Glyphs::update_glyph_color(Glyph* glyph, vec4 RGB_new){
  vector<vec4>& RGB = glyph->rgb;
  int size = RGB.size();
  //---------------------------

  //Change internal glyph color
  RGB.clear();
  for(int i=0; i<size; i++){
    RGB.push_back(RGB_new);
  }
  glyph->unicolor = RGB_new;

  //Reactualise vertex color data
  gpuManager->update_buffer_color(glyph);

  //---------------------------
}
void Glyphs::update_glyph_MinMax(Glyph* glyph){
  vector<vec3>& XYZ = glyph->xyz;
  vec3 min = XYZ[0];
  vec3 max = XYZ[0];
  vec3 centroid = vec3(0, 0, 0);
  //---------------------------

  for(int i=0; i<XYZ.size(); i++){
    for(int j=0; j<3; j++){
      if ( XYZ[i][j] <= min[j] ) min[j] = XYZ[i][j];
      if ( XYZ[i][j] >= max[j] ) max[j] = XYZ[i][j];
      centroid[j] += XYZ[i][j];
    }
  }

  for(int j=0;j<3;j++){
    centroid[j] /= XYZ.size();
  }

  //---------------------------
  glyph->min = min;
  glyph->max = max;
  glyph->COM = centroid;
}
*/

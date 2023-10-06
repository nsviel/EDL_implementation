#include "Data_node.h"
#include "Data_param.h"
#include "Scene/Scene.h"
#include "Scene/Database.h"
#include "Glyph/Glyphs.h"
#include "Load/Loader.h"


//Constructor / Destructor
Data_node::Data_node(Render_node* render_node){
  //---------------------------

  this->render_node = render_node;
  this->param_data = new Data_param();
  this->dataManager = new Database(this);
  this->sceneManager = new Scene(this);
  this->glyphManager = new Glyphs(this);
  this->loaderManager = new Loader(this);

  //---------------------------
}
Data_node::~Data_node(){
  //---------------------------

  delete param_data;
  delete sceneManager;
  delete dataManager;
  delete glyphManager;
  delete loaderManager;

  //---------------------------
}

void Data_node::init(){
  //---------------------------

  sceneManager->init_set();
  sceneManager->init_scene();
  glyphManager->create_glyph_scene();

  //---------------------------
}
void Data_node::reset(){
  //---------------------------

  sceneManager->reset_scene();

  //---------------------------
}

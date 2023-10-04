#include "Data_node.h"
#include "Data_param.h"
#include "Scene/Scene.h"
#include "Scene/Database.h"
#include "Glyph/Glyphs.h"
#include "Load/Loader.h"
#include "../Node.h"


//Constructor / Destructor
Data_node::Data_node(Node* node){
  //---------------------------

  this->node = node;
  this->core_node = node->get_core_node();

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

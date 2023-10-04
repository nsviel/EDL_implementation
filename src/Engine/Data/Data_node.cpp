#include "Data_node.h"
#include "Param_data.h"
#include "Scene/Scene.h"
#include "Scene/Database.h"
#include "Scene/Control.h"
#include "Glyph/Glyphs.h"
#include "Load/Loader.h"
#include "../Node.h"


//Constructor / Destructor
Data_node::Data_node(Node* node){
  //---------------------------

  this->node = node;
  this->node_core = node->get_node_core();

  this->param_data = new Param_data();
  this->dataManager = new Database(this);
  this->sceneManager = new Scene(this);
  this->glyphManager = new Glyphs(this);
  this->controlManager = new Control(this);
  this->loaderManager = new Loader(this);

  //---------------------------
}
Data_node::~Data_node(){
  //---------------------------

  delete param_data;
  delete sceneManager;
  delete dataManager;
  delete glyphManager;
  delete controlManager;

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

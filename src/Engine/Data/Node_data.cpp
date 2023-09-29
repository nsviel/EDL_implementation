#include "Node_data.h"

#include "Param_data.h"
#include "Scene/Scene.h"
#include "Scene/Database.h"
#include "Scene/Control.h"
#include "Glyph/Glyphs.h"

#include "../Load/Node_load.h"
#include "../Node.h"


//Constructor / Destructor
Node_data::Node_data(Node* node){
  //---------------------------

  this->node = node;
  this->node_engine = node->get_node_engine();

  this->param_data = new Param_data();
  this->dataManager = new Database(this);
  this->sceneManager = new Scene(this);
  this->glyphManager = new Glyphs(this);
  this->controlManager = new Control(this);

  //---------------------------
}
Node_data::~Node_data(){
  //---------------------------

  delete param_data;
  delete sceneManager;
  delete dataManager;
  delete glyphManager;
  delete controlManager;

  //---------------------------
}

void Node_data::init(){
  //---------------------------

  sceneManager->init_set();
  sceneManager->init_scene();
  glyphManager->create_glyph_scene();

  //---------------------------
}
void Node_data::reset(){
  //---------------------------

  sceneManager->reset_scene();

  //---------------------------
}

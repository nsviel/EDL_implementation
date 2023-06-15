#include "WIN_data.h"

#include "../Node_gui.h"
#include "../Param_gui.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Param_engine.h"
#include "../../Engine/Camera/struct_camera.h"


//Constructor / Destructor
WIN_data::WIN_data(Node_gui* node_gui, bool* show_window, string name) : WIN_base(show_window, name){
  //---------------------------

  Node_engine* node_engine = node_gui->get_node_engine();
  Param_engine* param_engine = node_engine->get_param_engine();
  this->camera = &param_engine->camera;

  //---------------------------
}
WIN_data::~WIN_data(){}

//Main function
void WIN_data::design_window(){
  //---------------------------

  this->object_parameter();

  //---------------------------
}

//Subfunction
void WIN_data::object_parameter(){
  //---------------------------


  //---------------------------
}

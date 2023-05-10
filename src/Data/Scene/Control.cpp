#include "Control.h"
#include "Scene.h"

#include "../Node_data.h"

#include "../../Engine/Dimension/Dimension.h"
#include "../../Engine/Camera/Camera.h"
#include "../../Engine/Node_engine.h"
#include "../../Operation/Transformation/Transformation.h"


//Constructor / Destructor
Control::Control(Node_data* node_data){
  //---------------------------

  Node_engine* node_engine = node_data->get_node_engine();
  this->dimManager = node_engine->get_dimManager();
  this->cameraManager = node_engine->get_cameraManager();
  this->sceneManager = node_data->get_sceneManager();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::exit(){
  GLFWwindow* window = dimManager->get_window();
  //---------------------------

  glfwSetWindowShouldClose(window, true);

  //---------------------------
}
void Control::reset(){
  //---------------------------

  cameraManager->reset_camera();

  //---------------------------
}
void Control::selected_object_translation(vec3 translation){
  Set* set_object = sceneManager->get_set_object();
  //---------------------------

  Transformation transformManager;
  transformManager.make_translation(set_object->selected_obj, translation);

  //---------------------------
}

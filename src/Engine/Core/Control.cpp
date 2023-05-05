#include "Control.h"

#include "../Dimension/Dimension.h"
#include "../Camera/Camera.h"
#include "../Node_engine.h"


//Constructor / Destructor
Control::Control(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->dimManager = node_engine->get_dimManager();
  this->cameraManager = node_engine->get_cameraManager();

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

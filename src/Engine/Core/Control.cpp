#include "Control.h"

#include "../Dimension/Dimension.h"
#include "../Node_engine.h"


//Constructor / Destructor
Control::Control(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->dimManager = node_engine->get_dimManager();

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

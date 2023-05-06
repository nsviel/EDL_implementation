#include "Node_engine.h"

#include "Vulkan/Engine.h"
#include "Core/Scene.h"
#include "Core/Control.h"
#include "Dimension/Dimension.h"
#include "Camera/Camera.h"
#include "Param_engine.h"

#include "../Node.h"


//Constructor / Destructor
Node_engine::Node_engine(Node* node){
  //---------------------------

  this->node = node;
  this->param_engine = new Param_engine();
  this->dimManager = new Dimension();
  this->cameraManager = new Camera(this);
  this->engineManager = new Engine(this);
  this->sceneManager = new Scene(this);
  this->controlManager = new Control(this);

  //---------------------------
}
Node_engine::~Node_engine(){
  //---------------------------

  delete dimManager;
  delete cameraManager;
  delete engineManager;
  delete sceneManager;
  delete controlManager;

  //---------------------------
}

//Main function
void Node_engine::init(){
  //---------------------------

  engineManager->init_vulkan();
  dimManager->update();
  engineManager->main_loop();

  //---------------------------
}
void Node_engine::loop(){
  //---------------------------

  cameraManager->input_cam_mouse();
  node->loop();

  //---------------------------
}
void Node_engine::exit(){
  //---------------------------

  engineManager->clean_vulkan();

  //---------------------------
}

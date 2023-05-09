#include "Node_engine.h"

#include "Vulkan/Engine.h"
#include "Core/Control.h"
#include "Dimension/Dimension.h"
#include "Camera/Camera.h"
#include "Param_engine.h"
#include "GPU/GPU_data.h"

#include "../Node.h"


//Constructor / Destructor
Node_engine::Node_engine(Node* node){
  //---------------------------

  this->node = node;
  this->param_engine = new Param_engine();
  this->dimManager = new Dimension();
  this->cameraManager = new Camera(this);
  this->engineManager = new Engine(this);
  this->controlManager = new Control(this);
  this->gpu_data = new GPU_data(this);

  //---------------------------
}
Node_engine::~Node_engine(){
  //---------------------------

  delete param_engine;
  delete dimManager;
  delete cameraManager;
  delete engineManager;
  delete controlManager;
  delete gpu_data;

  //---------------------------
}

//Main function
void Node_engine::init(){
  //---------------------------

  engineManager->init_vulkan();
  dimManager->update();

  //---------------------------
}
void Node_engine::loop_start(){
  //---------------------------

  engineManager->main_loop();

  //---------------------------
}
void Node_engine::loop(){
  //---------------------------

  cameraManager->input_cam_mouse();
  node->loop();
  gpu_data->loop_check_descriptor_update();

  //---------------------------
}
void Node_engine::exit(){
  //---------------------------

  engineManager->clean_vulkan();

  //---------------------------
}

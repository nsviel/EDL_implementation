#include "Node_engine.h"

#include "Vulkan/VK_engine.h"
#include "Dimension/Dimension.h"
#include "Camera/Camera.h"
#include "Param_engine.h"
#include "GPU/GPU_data.h"
#include "Shader/Source/EDL/Shader_edl.h"

#include "../Node.h"


//Constructor / Destructor
Node_engine::Node_engine(Node* node){
  //---------------------------

  this->node = node;
  this->param_engine = new Param_engine();
  this->dimManager = new Dimension();
  this->cameraManager = new Camera(this);
  this->shader_edl = new Shader_edl(this);
  this->vk_engine = new VK_engine(this);
  this->gpu_data = new GPU_data(this);

  //---------------------------
}
Node_engine::~Node_engine(){
  //---------------------------

  delete param_engine;
  delete dimManager;
  delete cameraManager;
  delete vk_engine;
  delete gpu_data;
  delete shader_edl;

  //---------------------------
}

//Main function
void Node_engine::init(){
  //---------------------------

  vk_engine->init_vulkan();
  dimManager->update();

  //---------------------------
}
void Node_engine::loop_start(){
  //---------------------------

  vk_engine->main_loop();

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

  vk_engine->clean_vulkan();

  //---------------------------
}
void Node_engine::reset(){
  //---------------------------

  cameraManager->reset_camera();

  //---------------------------
}

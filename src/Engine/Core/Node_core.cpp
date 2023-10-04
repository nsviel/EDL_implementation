#include "Node_core.h"

#include "Vulkan/VK_engine.h"
#include "Dimension/Dimension.h"
#include "Camera/Camera.h"
#include "Param_core.h"
#include "GPU/GPU_data.h"
#include "Shader/Shader.h"

#include "../Node.h"


//Constructor / Destructor
Node_core::Node_core(Node* node){
  //---------------------------

  this->node = node;
  this->param_engine = new Param_core();
  this->dimManager = new Dimension();
  this->cameraManager = new Camera(this);
  this->shaderManager = new Shader(this);
  this->vk_engine = new VK_engine(this);
  this->gpu_data = new GPU_data(this);

  //---------------------------
}
Node_core::~Node_core(){
  //---------------------------

  delete param_engine;
  delete dimManager;
  delete cameraManager;
  delete vk_engine;
  delete gpu_data;
  delete shaderManager;

  //---------------------------
}

//Main function
void Node_core::init(){
  //---------------------------

  vk_engine->init_vulkan();
  dimManager->update();

  //---------------------------
}
void Node_core::loop_start(){
  //---------------------------

  vk_engine->main_loop();

  //---------------------------
}
void Node_core::loop(){
  //---------------------------

  cameraManager->input_cam_mouse();
  node->loop();

  //---------------------------
}
void Node_core::exit(){
  //---------------------------

  vk_engine->clean_vulkan();

  //---------------------------
}
void Node_core::reset(){
  //---------------------------

  cameraManager->reset_camera();

  //---------------------------
}

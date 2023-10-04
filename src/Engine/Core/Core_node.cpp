#include "Core_node.h"

#include "Vulkan/VK_engine.h"
#include "Dimension/Dimension.h"
#include "Camera/Camera.h"
#include "Core_param.h"
#include "GPU/GPU_data.h"
#include "Shader/Shader.h"

#include "../Node.h"


//Constructor / Destructor
Core_node::Core_node(Node* node){
  //---------------------------

  this->node = node;
  this->core_param = new Core_param();
  this->dimManager = new Dimension();
  this->cameraManager = new Camera(this);
  this->shaderManager = new Shader(this);
  this->vk_engine = new VK_engine(this);
  this->gpu_data = new GPU_data(this);

  //---------------------------
}
Core_node::~Core_node(){
  //---------------------------

  delete core_param;
  delete dimManager;
  delete cameraManager;
  delete vk_engine;
  delete gpu_data;
  delete shaderManager;

  //---------------------------
}

//Main function
void Core_node::init(){
  //---------------------------

  vk_engine->init_vulkan();
  dimManager->update();

  //---------------------------
}
void Core_node::loop_start(){
  //---------------------------

  vk_engine->main_loop();

  //---------------------------
}
void Core_node::loop(){
  //---------------------------

  cameraManager->input_cam_mouse();
  node->loop();

  //---------------------------
}
void Core_node::exit(){
  //---------------------------

  vk_engine->clean_vulkan();

  //---------------------------
}
void Core_node::reset(){
  //---------------------------

  cameraManager->reset_camera();

  //---------------------------
}

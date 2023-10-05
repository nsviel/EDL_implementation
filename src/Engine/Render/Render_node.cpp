#include "Render_node.h"

#include "Vulkan/VK_engine.h"
#include "../../Element/Window/Dimension.h"
#include "Camera/Camera.h"
#include "Render_param.h"
#include "GPU/GPU_data.h"
#include "Shader/Shader.h"

#include "../Node.h"


//Constructor / Destructor
Render_node::Render_node(Node* node){
  //---------------------------

  this->node = node;
  this->core_param = new Render_param();
  this->dimManager = new Dimension();
  this->cameraManager = new Camera(this);
  this->shaderManager = new Shader(this);
  this->vk_engine = new VK_engine(this);
  this->gpu_data = new GPU_data(this);

  //---------------------------
}
Render_node::~Render_node(){
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
void Render_node::init(){
  //---------------------------

  vk_engine->init_vulkan();
  dimManager->update();

  //---------------------------
}
void Render_node::loop_start(){
  //---------------------------

  vk_engine->main_loop();

  //---------------------------
}
void Render_node::loop(){
  //---------------------------

  cameraManager->input_cam_mouse();
  node->loop();

  //---------------------------
}
void Render_node::exit(){
  //---------------------------

  vk_engine->clean_vulkan();

  //---------------------------
}
void Render_node::reset(){
  //---------------------------

  cameraManager->reset_camera();

  //---------------------------
}

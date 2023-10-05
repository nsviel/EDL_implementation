#include "Render_node.h"

#include "Vulkan/VK_engine.h"
#include "Camera/Camera.h"
#include "Render_param.h"
#include "GPU/GPU_data.h"
#include "Shader/Shader.h"

#include "../Node.h"

#include <Window/Window.h>


//Constructor / Destructor
Render_node::Render_node(Node* node){
  //---------------------------

  this->node = node;
  this->window = node->get_window();
  this->core_param = new Render_param();
  this->cameraManager = new Camera(this);
  this->shaderManager = new Shader(this);
  this->vk_engine = new VK_engine(this);
  this->gpu_data = new GPU_data(this);

  //---------------------------
}
Render_node::~Render_node(){
  //---------------------------

  delete core_param;
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
  window->compute_window_dim();

  //---------------------------
}
void Render_node::loop_start(){
  //---------------------------


  //---------------------------
}
void Render_node::loop(){
  //---------------------------


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

#include "Engine.h"
#include "Render/Render_node.h"
#include "Data/Data_node.h"
#include "Render/Vulkan/VK_engine.h"
#include <Camera/Camera.h>

#include <Window/Window.h>


//Constructor / Destructor
Engine::Engine(Window* window){
  //---------------------------

  this->window = window;
  this->render_node = new Render_node(window);
  this->data_node = new Data_node(render_node);

  //---------------------------
}
Engine::~Engine(){
  //---------------------------

  delete render_node;
  delete data_node;

  //---------------------------
}

void Engine::init(){
  //---------------------------

  render_node->init();
  data_node->init();

  //---------------------------
}
void Engine::loop(){
  VK_engine* vk_engine = render_node->get_vk_engine();
  Camera* cameraManager = render_node->get_cameraManager();
  //---------------------------

  cameraManager->input_cam_mouse();
  vk_engine->draw_frame();

  //---------------------------
}
void Engine::exit(){
  VK_engine* vk_engine = render_node->get_vk_engine();
  //---------------------------

  vk_engine->end_loop();
  render_node->exit();

  //---------------------------
}
void Engine::reset(){
  //---------------------------

  render_node->reset();
  data_node->reset();

  //---------------------------
}

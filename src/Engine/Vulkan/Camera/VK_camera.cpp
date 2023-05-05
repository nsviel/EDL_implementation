#include "VK_camera.h"

#include "../Engine_vulkan.h"

#include "../../Camera/Camera.h"
#include "../../Node_engine.h"


//Constructor / Destructor
VK_camera::VK_camera(Engine_vulkan* engine_vulkan){
  //---------------------------

  Node_engine* node_engine = engine_vulkan->get_node_engine();

  this->cameraManager = node_engine->get_cameraManager();

  //---------------------------
}
VK_camera::~VK_camera(){}

//Main function
MVP VK_camera:: get_mvp(){
  //---------------------------

  static auto startTime = std::chrono::high_resolution_clock::now();
  auto currentTime = std::chrono::high_resolution_clock::now();
  float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();



  MVP mvp{};
  mvp.model = mat4(1);
  mvp.view = cameraManager->compute_cam_view();
  mvp.proj = cameraManager->compute_cam_proj();



  //mvp.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f) * 0.1f, glm::vec3(0.0f, 0.0f, 1.0f));
  //mvp.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  //mvp.proj = glm::perspective(glm::radians(45.0f), 500 / (float) 500, 0.1f, 10.0f);
  //mvp.proj[1][1] *= -1; // Because glm is designed for OpenGL convention


  //---------------------------
  return mvp;
}

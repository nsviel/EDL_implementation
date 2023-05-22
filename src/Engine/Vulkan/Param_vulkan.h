#ifndef PARAM_VULKAN_H
#define PARAM_VULKAN_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Param_vulkan{
  //---------------------------

  //General parameters
  int max_frame = 2;
  std::string title = "Nephos";
  glm::vec2 window_dim = glm::vec2(1024, 500);
  glm::vec2 window_dim_min = glm::vec2(500, 250);
  std::string path_shader_vs = "../src/Engine/Shader/spir/shader_scene_vs.spv";
  std::string path_shader_fs = "../src/Engine/Shader/spir/shader_scene_fs.spv";

  //Vulkan objects
  VkExtent2D extent;
  VkPhysicalDevice physical_device;
  VkDevice device;
  VkInstance instance;

  //---------------------------
};

#endif

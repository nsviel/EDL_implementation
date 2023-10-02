#ifndef VK_PARAM_H
#define VK_PARAM_H

#include "Struct/struct_window.h"
#include "Struct/struct_instance.h"
#include "Struct/struct_device.h"
#include "Struct/struct_swapchain.h"
#include "Struct/struct_renderpass.h"
#include "Struct/struct_time.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct VK_param{
  //---------------------------

  int nb_frame;
  VkFormat required_image_format = VK_FORMAT_B8G8R8A8_UNORM; //VK_FORMAT_B8G8R8A8_SRGB

  Struct_window window = {
    "Nephos", //title
    glm::vec2(1024, 500), //dim
    glm::vec2(500, 250), ///dim_min
  };

  Struct_instance instance = {
    2, //max_frame_inflight
    "../src/Engine/Core/Shader/Code/spir/", //path_shader
  };

  Struct_device device;
  Struct_swapchain swapchain;
  Struct_time time;

  Struct_renderpass renderpass_scene;
  Struct_renderpass renderpass_edl;
  Struct_renderpass renderpass_psr;
  Struct_renderpass renderpass_ui;

  //---------------------------
};

#endif

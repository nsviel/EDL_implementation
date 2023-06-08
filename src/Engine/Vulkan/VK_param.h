#ifndef VK_PARAM_H
#define VK_PARAM_H

#include "Struct/struct_window.h"
#include "Struct/struct_instance.h"
#include "Struct/struct_device.h"
#include "Struct/struct_swapchain.h"
#include "Struct/struct_renderpass.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct VK_param{
  //---------------------------

  Struct_window window;
  Struct_instance instance;
  Struct_device device;
  Struct_swapchain swapchain;

  Struct_renderpass renderpass_scene;
  Struct_renderpass renderpass_render;
  Struct_renderpass renderpass_ui;

  //---------------------------
};

#endif

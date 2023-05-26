#ifndef PARAM_VULKAN_H
#define PARAM_VULKAN_H

#include "Struct/struct_instance.h"
#include "Struct/struct_device.h"
#include "Struct/struct_window.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Param_vulkan{
  //---------------------------

  Struct_instance instance;
  Struct_window window;
  Struct_device device;

  //---------------------------
};

#endif

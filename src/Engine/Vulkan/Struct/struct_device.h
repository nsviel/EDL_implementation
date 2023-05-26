#ifndef STRUCT_DEVICE_H
#define STRUCT_DEVICE_H

#include "../../../common.h"


struct Struct_device{
  VkPhysicalDevice physical_device;
  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
  vector<const char*> extension;
};


#endif

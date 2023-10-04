#ifndef STRUCT_INSTANCE_H
#define STRUCT_INSTANCE_H

#include "../../Core_common.h"


static VKAPI_ATTR VkBool32 VKAPI_CALL callback_debug(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData){
  //---------------------------

  std::cerr << "--------------------------" << std::endl;
  std::cerr << "[\033[1;32mVL\033[0m] " << pCallbackData->pMessage << std::endl;

  //---------------------------
  return VK_FALSE;
}

struct Struct_instance{
  //---------------------------

  int max_frame_inflight = 2;
  std::string path_shader = "../src/Engine/Render/Shader/Code/spir/";

  VkInstance instance;
  vector<const char*> extension;

  //---------------------------
};


#endif

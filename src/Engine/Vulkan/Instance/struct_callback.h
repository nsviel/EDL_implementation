#ifndef STRUCT_CALLBACK_H
#define STRUCT_CALLBACK_H

#include "../../../common.h"


static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData){
  //---------------------------

  std::cerr << "--------------------------" << std::endl;
  std::cerr << "[\033[1;32mVL\033[0m] " << pCallbackData->pMessage << std::endl;

  //---------------------------
  return VK_FALSE;
}

#endif

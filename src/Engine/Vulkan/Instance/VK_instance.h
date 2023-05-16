#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include "../../../common.h"

class Engine;


static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData){
  //---------------------------

  std::cerr << "--------------------------" << std::endl;
  std::cerr << "[\033[1;32mVL\033[0m] " << pCallbackData->pMessage << std::endl;

  //---------------------------
  return VK_FALSE;
}




class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance(Engine* engineManager);
  ~VK_instance();

public:
  //Main functions
  void create_instance();
  void cleanup();

  //Validation layers
  std::vector<const char*> get_required_extensions();

  inline VkInstance get_instance(){return instance;}

private:
  Engine* engineManager;
  VkInstance instance;
};

#endif

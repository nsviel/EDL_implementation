#include "VK_binding.h"

#include "../Engine.h"
#include "../Param_vulkan.h"


//Constructor / Destructor
VK_binding::VK_binding(Engine* engineManager){
  //---------------------------

  this->param_vulkan = engineManager->get_param_vulkan();

  //---------------------------
}
VK_binding::~VK_binding(){}

//Main function

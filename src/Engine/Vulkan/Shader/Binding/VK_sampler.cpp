#include "VK_sampler.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Data/VK_buffer.h"


//Constructor / Destructor
VK_sampler::VK_sampler(VK_engine* vk_engine){
  //---------------------------

  this->vk_param = vk_engine->get_vk_param();
  this->vk_buffer = vk_engine->get_vk_buffer();

  //---------------------------
}
VK_sampler::~VK_sampler(){}

//Main function

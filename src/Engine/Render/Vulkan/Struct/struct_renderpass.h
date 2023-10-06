#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include "struct_frame.h"
#include "struct_pipeline.h"
#include "struct_viewport.h"
#include "struct_subpass.h"
#include <Specific/common.h>


struct Struct_renderpass{
  //---------------------------

  Struct_pipeline* get_pipeline_byName(string name){
    for(int i=0; i<vec_pipeline.size(); i++){
      if(vec_pipeline[i]->name == name){
        return vec_pipeline[i];
      }
    }
    cout<<"[error] Pipeline by name error -> not found"<<endl;
    return nullptr;
  }

  //Info
  std::string name;

  //Renderpass frame set
  VkImageUsageFlags color_image_usage;
  VkImageLayout color_sampler_layout;
  VkImageUsageFlags depth_image_usage;
  VkImageLayout depth_sampler_layout;
  Frame* get_rendering_frame(){return vec_frame[rendering_frame_ID];}
  uint32_t rendering_frame_ID = 0;
  std::vector<Frame*> vec_frame;

  //Render pass elements
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;

  //Attachment
  std::vector<Struct_pipeline*> vec_pipeline;
  std::vector<Struct_subpass*> vec_subpass;

  VkSemaphore semaphore_to_wait;
  VkSemaphore semaphore_to_run;
  VkFence fence;

  //---------------------------
};


#endif

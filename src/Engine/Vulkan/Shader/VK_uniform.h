#ifndef VK_UNIFORM_H
#define VK_UNIFORM_H

#include "../Struct/struct_mvp.h"
#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;
class VK_buffer;
class VK_swapchain;
class VK_camera;


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(Engine* engineManager);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers(vector<Struct_pipeline*> vec_pipeline);
  void update_uniform_buffer(Struct_pipeline* pipeline, MVP& mvp);
  void clean_uniform(Struct_pipeline* pipeline);

  inline vector<VkBuffer> get_uniformBuffers(){return uniform_buffer;};

private:
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
  VK_buffer* vk_buffer;
  VK_swapchain* vk_swapchain;
  VK_camera* vk_camera;

  vector<VkBuffer> uniform_buffer;
  vector<VkDeviceMemory> uniform_buffer_memory;
  vector<void*> uniform_buffer_mapped;
};

#endif

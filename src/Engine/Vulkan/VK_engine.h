#ifndef VK_ENGINE_H
#define VK_ENGINE_H

#include "Struct/typedef.h"
#include "../../common.h"

class Node_engine;
class VK_param;
class Param_engine;

class VK_window;
class VK_instance;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_pipeline;
class VK_framebuffer;
class VK_command;
class VK_synchronization;
class VK_drawing;
class VK_buffer;
class VK_descriptor;
class VK_uniform;
class VK_texture;
class VK_depth;
class VK_data;
class VK_viewport;
class VK_gui;
class VK_camera;
class VK_shader;
class VK_physical_device;
class VK_frame;
class VK_validation;
class VK_canvas;
class VK_color;
class VK_binding;


class VK_engine
{
public:
  //Constructor / Destructor
  VK_engine(Node_engine* node_engine);
  ~VK_engine();

public:
  //Main functions
  void init_vulkan();
  void main_loop();
  void clean_vulkan();

  //Subfunction
  void fps_control(const std::chrono::time_point<std::chrono::steady_clock>& start);
  void fps_calcul(std::chrono::steady_clock::time_point& start_time);

  inline Node_engine* get_node_engine(){return node_engine;}
  inline Param_engine* get_param_engine(){return param_engine;}
  inline VK_param* get_vk_param(){return vk_param;}
  inline VK_device* get_vk_device(){return vk_device;}
  inline VK_framebuffer* get_vk_framebuffer(){return vk_framebuffer;}
  inline VK_window* get_vk_window(){return vk_window;}
  inline VK_swapchain* get_vk_swapchain(){return vk_swapchain;}
  inline VK_synchronization* get_vk_synchronization(){return vk_synchronization;}
  inline VK_command* get_vk_command(){return vk_command;}
  inline VK_instance* get_vk_instance(){return vk_instance;}
  inline VK_renderpass* get_vk_renderpass(){return vk_renderpass;}
  inline VK_pipeline* get_vk_pipeline(){return vk_pipeline;}
  inline VK_buffer* get_vk_buffer(){return vk_buffer;}
  inline VK_descriptor* get_vk_descriptor(){return vk_descriptor;}
  inline VK_texture* get_vk_texture(){return vk_texture;}
  inline VK_depth* get_vk_depth(){return vk_depth;}
  inline VK_color* get_vk_color(){return vk_color;}
  inline VK_data* get_vk_data(){return vk_data;}
  inline VK_viewport* get_vk_viewport(){return vk_viewport;}
  inline VK_gui* get_vk_gui(){return vk_gui;}
  inline VK_camera* get_vk_camera(){return vk_camera;}
  inline VK_shader* get_vk_shader(){return vk_shader;}
  inline VK_physical_device* get_vk_physical_device(){return vk_physical_device;}
  inline VK_frame* get_vk_frame(){return vk_frame;}
  inline VK_validation* get_vk_validation(){return vk_validation;}
  inline VK_drawing* get_vk_drawing(){return vk_drawing;}
  inline VK_canvas* get_vk_canvas(){return vk_canvas;}
  inline VK_binding* get_vk_binding(){return vk_binding;}

  inline float get_time_init(){return time_init;}
  inline float get_time_fps(){return time_fps;}

private:
  Node_engine* node_engine;
  VK_param* vk_param;
  Param_engine* param_engine;

  VK_window* vk_window;
  VK_instance* vk_instance;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_pipeline* vk_pipeline;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
  VK_binding* vk_binding;
  VK_synchronization* vk_synchronization;
  VK_drawing* vk_drawing;
  VK_buffer* vk_buffer;
  VK_descriptor* vk_descriptor;
  VK_depth* vk_depth;
  VK_texture* vk_texture;
  VK_data* vk_data;
  VK_viewport* vk_viewport;
  VK_gui* vk_gui;
  VK_camera* vk_camera;
  VK_shader* vk_shader;
  VK_physical_device* vk_physical_device;
  VK_frame* vk_frame;
  VK_validation* vk_validation;
  VK_canvas* vk_canvas;
  VK_color* vk_color;

  float time_init;
  float time_fps;
};

#endif

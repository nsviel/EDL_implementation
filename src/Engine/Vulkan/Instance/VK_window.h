#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#include "../../../common.h"

class Engine;
class Dimension;
class Param_engine;
class VK_instance;
class VK_viewport;


class VK_window
{
public:
  //Constructor / Destructor
  VK_window(Engine* engineManager);
  ~VK_window();

public:
  //Main functions
  void init_window();
  void clean_surface();
  void clean_window();

  //Subfunction
  void create_window_surface();
  glm::vec2 get_framebuffer_size();
  bool check_for_resizing();

  inline GLFWwindow* get_window(){return window;}
  inline VkSurfaceKHR get_surface(){return surface;}

private:
  GLFWwindow* window;
  Param_engine* param_engine;
  Dimension* dimManager;
  VK_instance* vk_instance;
  VK_viewport* vk_viewport;

  VkSurfaceKHR surface;
  glm::vec2 window_dim;
};

#endif
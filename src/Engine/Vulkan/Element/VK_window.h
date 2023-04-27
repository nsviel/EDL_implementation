#ifndef VK_WINDOW_H
#define VK_WINDOW_H

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Engine_vulkan;
class Node_engine;
class VK_instance;


class VK_window
{
public:
  //Constructor / Destructor
  VK_window(Engine_vulkan* engine_vulkan);
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
  glm::vec2 render_dim;
  VkSurfaceKHR surface;
  VK_instance* vk_instance;
};

#endif

#ifndef GUI_H
#define GUI_H

class Node_engine;
class VK_window;
class VK_instance;
class VK_device;
class VK_renderpass;
class Engine_vulkan;


class GUI
{
public:
  //Constructor / Destructor
  GUI(Node_engine* node_engine);
  ~GUI();

public:
  //Main functions
  void init();
  void cleanup();

  void loop();
  void loop_start();
  void loop_end();

  void show_basic_stuff();

private:
  VK_window* vk_window;
  VK_instance* vk_instance;
  VK_device* vk_device;
  VK_renderpass* vk_renderpass;
  Engine_vulkan* engine_vulkan;
};

#endif

#include "Window.h"


//Constructor / Destructor
Window::Window(){
  //---------------------------

  this->has_been_resized = false;

  //---------------------------
}
Window::~Window(){}

//Main function
void Window::create_window(int width, int height, string title){
  //---------------------------

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  this->window_dim = glm::vec2(width, height);
  this->get_required_extensions();

  if (!glfwVulkanSupported()){
    printf("GLFW: Vulkan Not Supported\n");
    exit(0);
  }

  //---------------------------
}
void Window::destroy_window(){
  //---------------------------

  glfwDestroyWindow(window);
  glfwTerminate();

  //---------------------------
}

//Subfunction
void Window::create_window_surface(VkInstance& instance, VkSurfaceKHR& surface){
  //---------------------------

  VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}
void Window::set_window_size_minimum(int width, int height){
  //---------------------------

  glfwSetWindowSizeLimits(window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);

  //---------------------------
}
void Window::set_window_size_maximum(int width, int height){
  //---------------------------

  glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, width, height);

  //---------------------------
}

//Operation function
bool Window::check_for_resizing(){
  //---------------------------

  vec2 dim = get_framebuffer_size();
  if(dim.x != window_dim.x || dim.y != window_dim.y){
    this->has_been_resized = true;
    this->window_dim = dim;
  }

  //---------------------------
  return has_been_resized;
}
vec2 Window::get_framebuffer_size(){
  vec2 dim = vec2(0);
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  dim.x = width;
  dim.y = height;

  //---------------------------
  return dim;
}
vector<const char*> Window::get_required_extensions(){
  //---------------------------

  uint32_t glfw_extension_nb = 0;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_nb);
  vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_nb);

  for(int i=0; i<extensions.size(); i++){
    vec_extension.push_back(extensions[i]);
  }

  //---------------------------
  return vec_extension;
}

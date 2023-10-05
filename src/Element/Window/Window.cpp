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
void Window::close_window(){
  //---------------------------

  glfwSetWindowShouldClose(window, true);

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

  vec2 dim = compute_framebuffer_size();
  if(dim.x != window_dim.x || dim.y != window_dim.y){
    this->has_been_resized = true;
    this->window_dim = dim;
  }

  //---------------------------
  return has_been_resized;
}
vec2 Window::compute_framebuffer_size(){
  vec2 dim = vec2(0);
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  this->window_dim = vec2(width, height);
  this->window_center = glm::vec2(width/2, height/2);

  //---------------------------
  return window_dim;
}
vector<const char*> Window::get_required_extensions(){
  //---------------------------

  uint32_t glfw_extension_nb = 0;
  const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_nb);
  vector<const char*> extensions(glfw_extensions, glfw_extensions + glfw_extension_nb);

  vector<const char*> vec_extension;
  for(int i=0; i<extensions.size(); i++){
    vec_extension.push_back(extensions[i]);
  }

  //---------------------------
  return vec_extension;
}

glm::vec2 Window::get_mouse_pose(){

  //---------------------------

  std::cout <<"hello"<<std::endl;

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  std::cout <<xpos<<std::endl;
  glm::vec2 pos = glm::vec2(xpos, ypos);

  std::cout <<"hello"<<std::endl;

  //---------------------------
  return pos;
}
void Window::set_mouse_pose(glm::vec2 pos){
  //---------------------------

  glfwSetCursorPos(window, pos.x, pos.y);

  //---------------------------
}

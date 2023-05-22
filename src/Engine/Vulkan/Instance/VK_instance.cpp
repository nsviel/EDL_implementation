#include "VK_instance.h"
#include "VK_validation.h"

#include "../Engine.h"
#include "../Param_vulkan.h"


//Constructor / Destructor
VK_instance::VK_instance(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();

  //---------------------------
}
VK_instance::~VK_instance(){}

//Main function
void VK_instance::create_instance(){
  //The instance is the connection between application and Vulkan library
  VK_validation* vk_validation = engineManager->get_vk_validation();
  bool with_validation_layer = vk_validation->get_with_validation_layer();
  //---------------------------

  //Application info
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  //Instance info
  auto extensions = get_required_extensions();
  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  createInfo.ppEnabledExtensionNames = extensions.data();

  vector<const char*> validation_layers = vk_validation->get_validation_layers();
  if(with_validation_layer){
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    vk_validation->populateDebugMessengerCreateInfo(debugCreateInfo);

    createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
    createInfo.ppEnabledLayerNames = validation_layers.data();
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
  }else{
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
  }

  //Create instance
  VkResult result = vkCreateInstance(&createInfo, nullptr, &param_vulkan->instance);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create instance!");
  }

  //---------------------------
}
void VK_instance::cleanup(){
  //---------------------------

  vkDestroyInstance(param_vulkan->instance, nullptr);

  //---------------------------
}

//Validation layers
vector<const char*> VK_instance::get_required_extensions(){
  //Return the required list of extensions based on whether validation layers are enabled or not
  VK_validation* vk_validation = engineManager->get_vk_validation();
  bool with_validation_layer = vk_validation->get_with_validation_layer();
  //---------------------------

  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  if(with_validation_layer){
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  //---------------------------
  return extensions;
}

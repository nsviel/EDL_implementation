#include "VK_instance.h"

#include "../../Node_engine.h"


//Constructor / Destructor
VK_instance::VK_instance(){
  //---------------------------



  //---------------------------
}
VK_instance::~VK_instance(){}

//Main function
void VK_instance::init_instance(){
  //---------------------------

  this->create_instance();
  this->create_validationLayer();

  //---------------------------
}
void VK_instance::create_instance(){
  //The instance is the connection between application and Vulkan library
  //---------------------------

  //List of all validation layers
  std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
  };

  //Check validation layers
  if(with_validation_layer && !check_validationLayer_support(validationLayers)){
    throw std::runtime_error("[error] validation layers requested, but not available!");
  }

  //Application info
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  //Instance info
  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  auto extensions = get_required_extensions();
  createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
  createInfo.ppEnabledExtensionNames = extensions.data();

  VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
  if(with_validation_layer){
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();

    populateDebugMessengerCreateInfo(debugCreateInfo);
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
  }else{
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
  }

  //Instance extensions
  /*  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;
  createInfo.enabledLayerCount = 0;*/

  //Create instance
  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create instance!");
  }

  //---------------------------
}
void VK_instance::create_validationLayer(){
  //---------------------------

  if(!with_validation_layer) return;

  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  populateDebugMessengerCreateInfo(createInfo);

  VkResult result = CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to set up debug messenger!");
  }

  //---------------------------
}
void VK_instance::cleanup(){
  //---------------------------

  if(with_validation_layer){
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
  }

  vkDestroyInstance(instance, nullptr);

  //---------------------------
}

//Validation layers
bool VK_instance::check_validationLayer_support(std::vector<const char*> validationLayers){
  //---------------------------

  //Checks if all of the requested layers are available
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  //Check if all of the layers in validationLayers exist in the availableLayers list
  for(const char* layerName : validationLayers){
    bool layerFound = false;

    for(const auto& layerProperties : availableLayers){
      if(strcmp(layerName, layerProperties.layerName) == 0){
        layerFound = true;
        break;
      }
    }

    if(!layerFound){
      return false;
    }
  }

  //---------------------------
  return true;
}
std::vector<const char*> VK_instance::get_required_extensions(){
  //Return the required list of extensions based on whether validation layers are enabled or not
  //---------------------------

  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

  if(with_validation_layer){
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }

  //---------------------------
  return extensions;
}
VkResult VK_instance::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
  //---------------------------

  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }

  //---------------------------
}
void VK_instance::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
  //---------------------------

  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }

  //---------------------------
}
void VK_instance::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo){
  //---------------------------

  createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = debugCallback;

  //---------------------------
}
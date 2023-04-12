#include "Engine_vulkan.h"

#include "Engine_window.h"

#include "../Node_engine.h"

#include <vector>
#include <set>
#include <glm/glm.hpp>
#include <algorithm>
#include <fstream>

const int MAX_FRAMES_IN_FLIGHT = 2;
uint32_t currentFrame = 0;


//Constructor / Destructor
Engine_vulkan::Engine_vulkan(Node_engine* node_engine){
  //---------------------------

  this->engine_window = node_engine->get_engine_window();

  //---------------------------
}
Engine_vulkan::~Engine_vulkan(){}

//Main function
void Engine_vulkan::init_vulkan(){
  //---------------------------

  this->create_instance();
  this->create_window_surface();
  this->select_physical_device();
  this->create_logical_device();
  this->create_swapChain();
  this->create_image_views();
  this->create_render_pass();
  this->create_graphics_pipeline();
  this->create_framebuffers();
  this->create_command_pool();
  this->create_command_buffers();
  this->create_sync_objects();

  //---------------------------
}
void Engine_vulkan::main_loop() {
  GLFWwindow* window = engine_window->get_window();
  //---------------------------

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    this->draw_frame();
  }

  vkDeviceWaitIdle(device);

  //---------------------------
}
void Engine_vulkan::draw_frame(){
  //---------------------------

  framebufferResized = engine_window->check_for_resizing();

  //Waiting for the previous frame
  vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  uint32_t imageIndex;
  VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    this->recreate_swapChain();
    return;
  } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetFences(device, 1, &inFlightFences[currentFrame]);

  //If window resized
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    this->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  vkResetCommandBuffer(commandBuffers[currentFrame], 0);
  record_command_buffer(commandBuffers[currentFrame], imageIndex);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 1;
  submitInfo.pWaitSemaphores = waitSemaphores;
  submitInfo.pWaitDstStageMask = waitStages;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffers[currentFrame];
  VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
  submitInfo.signalSemaphoreCount = 1;
  submitInfo.pSignalSemaphores = signalSemaphores;

  result = vkQueueSubmit(queue_graphics, 1, &submitInfo, inFlightFences[currentFrame]);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentInfo.waitSemaphoreCount = 1;
  presentInfo.pWaitSemaphores = signalSemaphores;

  VkSwapchainKHR swapChains[] = {swapChain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &imageIndex;
  presentInfo.pResults = nullptr; // Optional

  result = vkQueuePresentKHR(queue_presentation, &presentInfo);
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized){
    this->framebufferResized = false;
    this->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;

  //---------------------------
}
void Engine_vulkan::clean_vulkan(){
  //---------------------------

  this->cleanup_swapChain();

  vkDestroyPipeline(device, graphicsPipeline, nullptr);
  vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
  vkDestroyRenderPass(device, renderPass, nullptr);

  for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
    vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
    vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
    vkDestroyFence(device, inFlightFences[i], nullptr);
  }

  vkDestroyCommandPool(device, commandPool, nullptr);
  vkDestroyDevice(device, nullptr);
  vkDestroySurfaceKHR(instance, surface, nullptr);
  vkDestroyInstance(instance, nullptr);

  //---------------------------
}

//Subfunction
void Engine_vulkan::create_instance(){
  //The instance is the connection between application and Vulkan library
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
  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  //Instance extensions
  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;
  createInfo.enabledLayerCount = 0;

  //Create instance
  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create instance!");
  }

  //---------------------------
}
void Engine_vulkan::create_window_surface(){
  GLFWwindow* window = engine_window->get_window();
  //---------------------------

  VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}
void Engine_vulkan::create_logical_device(){
  //Interface between selected GPU and application
  //---------------------------

  //Get GPU qeue families
  struct_queueFamily_indices indices = find_queue_families(physical_device);

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> uniqueQueueFamilies = {
    indices.family_graphics.value(),
    indices.family_presentation.value()
  };

  float queuePriority = 1.0f;
  for (uint32_t queueFamily : uniqueQueueFamilies) {
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfo);
  }

  //Specifying used device features
  VkPhysicalDeviceFeatures deviceFeatures{};

  //Logical device info
  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.pQueueCreateInfos = queueCreateInfos.data();
  createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
  createInfo.pEnabledFeatures = &deviceFeatures;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(required_extensions.size());
  createInfo.ppEnabledExtensionNames = required_extensions.data();
  createInfo.enabledLayerCount = 0;

  //Creating the logical device
  VkResult result = vkCreateDevice(physical_device, &createInfo, nullptr, &device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create logical device!");
  }

  //Get queue family handles
  vkGetDeviceQueue(device, indices.family_graphics.value(), 0, &queue_graphics);
  vkGetDeviceQueue(device, indices.family_presentation.value(), 0, &queue_presentation);

  //---------------------------
}
void Engine_vulkan::create_swapChain(){
  //---------------------------

  //Get swap chain
  struct_swapChain_details swapChain_setting = find_swapChain_details(physical_device);

  //Retrieve settings
  VkSurfaceFormatKHR surfaceFormat = swapChain_surface_format(swapChain_setting.formats);
  VkPresentModeKHR presentation_mode = swapChain_presentation_mode(swapChain_setting.mode_presentation);
  VkExtent2D extent = swapChain_extent_setting(swapChain_setting.capabilities);

  //Get swap chain image capacity (0 means no maximum)
  uint32_t nb_image = swapChain_setting.capabilities.minImageCount + 1;
  if(swapChain_setting.capabilities.maxImageCount > 0 && nb_image > swapChain_setting.capabilities.maxImageCount){
    nb_image = swapChain_setting.capabilities.maxImageCount;
  }

  //Create swap chain info
  VkSwapchainCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = surface;
  createInfo.minImageCount = nb_image;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing

  //Link with queue families
  struct_queueFamily_indices indices = find_queue_families(physical_device);
  uint32_t queueFamilyIndices[] = {indices.family_graphics.value(), indices.family_presentation.value()};

  if(indices.family_graphics != indices.family_presentation){
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  }else{
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0; // Optional
    createInfo.pQueueFamilyIndices = nullptr; // Optional
  }

  createInfo.preTransform = swapChain_setting.capabilities.currentTransform;
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Ignore alpha channel
  createInfo.presentMode = presentation_mode;
  createInfo.clipped = VK_TRUE;
  createInfo.oldSwapchain = VK_NULL_HANDLE;

  //Create swap chain
  VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create swap chain!");
  }

  //Swap chain handler
  vkGetSwapchainImagesKHR(device, swapChain, &nb_image, nullptr);
  swapChain_images.resize(nb_image);
  vkGetSwapchainImagesKHR(device, swapChain, &nb_image, swapChain_images.data());

  //Store values
  this->swapChain_image_format = surfaceFormat.format;
  this->swapChain_extent = extent;

  //---------------------------
}
void Engine_vulkan::create_image_views(){
  //---------------------------

  //Resize the image view vector
  swapChain_image_views.resize(swapChain_images.size());

  //Image view settings & creation
  for (size_t i = 0; i < swapChain_images.size(); i++) {
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = swapChain_images[i];
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = swapChain_image_format;
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    VkResult result = vkCreateImageView(device, &createInfo, nullptr, &swapChain_image_views[i]);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create image views!");
    }
  }

  //---------------------------
}
void Engine_vulkan::create_render_pass(){
  //---------------------------

  //Attachement description
  VkAttachmentDescription colorAttachment{};
  colorAttachment.format = swapChain_image_format;
  colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
  colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  //Attachment references
  VkAttachmentReference colorAttachmentRef{};
  colorAttachmentRef.attachment = 0;
  colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  //Subpasses
  VkSubpassDescription subpass{};
  subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass.colorAttachmentCount = 1;
  subpass.pColorAttachments = &colorAttachmentRef;

  VkSubpassDependency dependency{};
  dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  dependency.dstSubpass = 0;
  dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.srcAccessMask = 0;
  dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

  //Render pass info
  VkRenderPassCreateInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.attachmentCount = 1;
  renderPassInfo.pAttachments = &colorAttachment;
  renderPassInfo.subpassCount = 1;
  renderPassInfo.pSubpasses = &subpass;
  renderPassInfo.dependencyCount = 1;
  renderPassInfo.pDependencies = &dependency;

  //Render pass creation
  VkResult result = vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
void Engine_vulkan::create_graphics_pipeline(){
  //---------------------------

  //Load spir format shaders
  auto code_vert = read_file("../src/Engine/Shader/spir/vert.spv");
  auto code_frag = read_file("../src/Engine/Shader/spir/frag.spv");

  //Create associated shader modules
  VkShaderModule module_vert = create_shader_module(code_vert);
  VkShaderModule module_frag = create_shader_module(code_frag);

  //Vertex shader link in pipeline
  VkPipelineShaderStageCreateInfo info_vert{};
  info_vert.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_vert.stage = VK_SHADER_STAGE_VERTEX_BIT;
  info_vert.module = module_vert;
  info_vert.pName = "main";
  info_vert.pSpecializationInfo = nullptr;

  //Fragment shader link in pipeline
  VkPipelineShaderStageCreateInfo info_frag{};
  info_frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  info_frag.module = module_frag;
  info_frag.pName = "main";
  info_frag.pSpecializationInfo = nullptr;

  //Shader info array
  VkPipelineShaderStageCreateInfo shaderStages[] = {info_vert, info_frag};

  //Vertex input settings
  VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
  vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexInputInfo.vertexBindingDescriptionCount = 0;
  vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
  vertexInputInfo.vertexAttributeDescriptionCount = 0;
  vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional

  //Drawing topology
  VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  //Viewport
  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width  = (float) swapChain_extent.width;
  viewport.height = (float) swapChain_extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  //Dynamic internal variables (viewport, line width, ...)
  //the subsequent values has to be given at runtime
  std::vector<VkDynamicState> dynamicStates = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
  };
  VkPipelineDynamicStateCreateInfo dynamicState{};
  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
  dynamicState.pDynamicStates = dynamicStates.data();

  //Full viewport scissor
  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = swapChain_extent;

  //Viewport info
  VkPipelineViewportStateCreateInfo viewportState{};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.scissorCount = 1;

  //Rasterization stage
  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f; // Optional
  rasterizer.depthBiasClamp = 0.0f; // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

  //Multisampling -> disabled
  VkPipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f; // Optional
  multisampling.pSampleMask = nullptr; // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
  multisampling.alphaToOneEnable = VK_FALSE; // Optional

  //Color blending stage
  VkPipelineColorBlendAttachmentState colorBlendAttachment{};
  colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_FALSE;
  colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  VkPipelineColorBlendStateCreateInfo colorBlending{};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f; // Optional
  colorBlending.blendConstants[1] = 0.0f; // Optional
  colorBlending.blendConstants[2] = 0.0f; // Optional
  colorBlending.blendConstants[3] = 0.0f; // Optional

  //Pipeline layout info -> usefull for shader uniform variables
  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0; // Optional
  pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
  pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

  //Pipeline layout creation
  VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create pipeline layout!");
  }

  //Final graphics pipeline info
  VkGraphicsPipelineCreateInfo pipelineInfo{};
  pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipelineInfo.stageCount = 2;
  pipelineInfo.pStages = shaderStages;
  pipelineInfo.pVertexInputState = &vertexInputInfo;
  pipelineInfo.pInputAssemblyState = &inputAssembly;
  pipelineInfo.pViewportState = &viewportState;
  pipelineInfo.pRasterizationState = &rasterizer;
  pipelineInfo.pMultisampleState = &multisampling;
  pipelineInfo.pDepthStencilState = nullptr; // Optional
  pipelineInfo.pColorBlendState = &colorBlending;
  pipelineInfo.pDynamicState = &dynamicState;
  pipelineInfo.layout = pipelineLayout;
  pipelineInfo.renderPass = renderPass;
  pipelineInfo.subpass = 0;
  pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipelineInfo.basePipelineIndex = -1; // Optional

  //Final graphics pipeline creation
  VkResult result_pipe = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);
  if(result_pipe != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create graphics pipeline!");
  }

  //Destroy shader modules
  vkDestroyShaderModule(device, module_vert, nullptr);
  vkDestroyShaderModule(device, module_frag, nullptr);

  //---------------------------
}
void Engine_vulkan::create_framebuffers(){
  //---------------------------

  //Resize to hold all fbos
  swapChain_fbo.resize(swapChain_image_views.size());

  //Create frambuffer
  for(size_t i=0; i<swapChain_image_views.size(); i++){
    VkImageView attachments[] = {
      swapChain_image_views[i]
    };

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
    framebufferInfo.width = swapChain_extent.width;
    framebufferInfo.height = swapChain_extent.height;
    framebufferInfo.layers = 1;

    VkResult result = vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChain_fbo[i]);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create framebuffer!");
    }
  }


  //---------------------------
}
void Engine_vulkan::create_command_pool(){
  //---------------------------

  struct_queueFamily_indices queueFamily_indices = find_queue_families(physical_device);

  //Command pool info
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = queueFamily_indices.family_graphics.value();

  //Command pool creation
  VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void Engine_vulkan::create_command_buffers(){
  //---------------------------

  commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

  //Command buffer allocation
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = commandPool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();

  VkResult result = vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  //---------------------------
}
void Engine_vulkan::create_sync_objects(){
  //---------------------------

  imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
  inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

  //Semaphore info
  VkSemaphoreCreateInfo semaphoreInfo{};
  semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

  //Fence info
  VkFenceCreateInfo fenceInfo{};
  fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

  //Semaphore and fence creation
 for(size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++){
    VkResult result_sema_1 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]);
    VkResult result_sema_2 = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]);
    VkResult result_hence = vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]);
    if(result_sema_1 != VK_SUCCESS || result_sema_2 != VK_SUCCESS || result_hence != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create semaphores!");
    }
  }

  //---------------------------
}

//Misc function
void Engine_vulkan::select_physical_device(){
  //---------------------------

  this->physical_device = VK_NULL_HANDLE;

  //Find how many GPU are available
  uint32_t nb_device = 0;
  vkEnumeratePhysicalDevices(instance, &nb_device, nullptr);
  if (nb_device == 0) {
    throw std::runtime_error("failed to find GPUs with Vulkan support!");
  }

  //List all available GPU and take suitable one
  std::vector<VkPhysicalDevice> devices(nb_device);
  vkEnumeratePhysicalDevices(instance, &nb_device, devices.data());
  for (const auto& device : devices) {
    if (is_device_suitable(device)) {
      physical_device = device;
      break;
    }
  }
  if (physical_device == VK_NULL_HANDLE) {
    throw std::runtime_error("failed to find a suitable GPU!");
  }

  //---------------------------
}
bool Engine_vulkan::is_device_suitable(VkPhysicalDevice device){
  //---------------------------

  //Queue suitable
  struct_queueFamily_indices queue_indices = find_queue_families(device);
  bool queue_ok = queue_indices.is_complete();

  //Extension suitable
  bool extension_ok = check_extension_support(device);

  //Swap chain suitable
  bool swapChain_ok = false;
  if(extension_ok){
    struct_swapChain_details swapChain_setting = find_swapChain_details(device);
    swapChain_ok = !swapChain_setting.formats.empty() && !swapChain_setting.mode_presentation.empty();
  }

  //---------------------------
  return queue_ok && extension_ok && swapChain_ok;
}
bool Engine_vulkan::check_extension_support(VkPhysicalDevice device){
  //---------------------------

  //Get device extension number
  uint32_t nb_extension;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &nb_extension, nullptr);

  //List device extension
  std::vector<VkExtensionProperties> vec_extension(nb_extension);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &nb_extension, vec_extension.data());

  //Check if all required extension are in the list
  std::set<std::string> requiredExtensions(required_extensions.begin(), required_extensions.end());
  for (const auto& extension : vec_extension) {
    requiredExtensions.erase(extension.extensionName);
  }

  //---------------------------
  return requiredExtensions.empty();
}
struct_swapChain_details Engine_vulkan::find_swapChain_details(VkPhysicalDevice device){
  struct_swapChain_details details;
  //---------------------------

  //Get basic surface capabilities
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

  //Get supported surface format number
  uint32_t nb_format;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &nb_format, nullptr);

  //Get supported surface format list
  if(nb_format != 0){
    details.formats.resize(nb_format);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &nb_format, details.formats.data());
  }

  //Get presentation mode number
  uint32_t nb_mode_presentation;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &nb_mode_presentation, nullptr);

  //Get presentation mode list
  if(nb_mode_presentation != 0){
    details.mode_presentation.resize(nb_mode_presentation);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &nb_mode_presentation, details.mode_presentation.data());
  }

  //---------------------------
  return details;
}
struct_queueFamily_indices Engine_vulkan::find_queue_families(VkPhysicalDevice device){
  struct_queueFamily_indices indices;
  //---------------------------

  //Get queue family number
  uint32_t nb_queueFamily = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &nb_queueFamily, nullptr);
  if(nb_queueFamily == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(nb_queueFamily);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &nb_queueFamily, vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily) {
    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.family_graphics = i;
    }

    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
    if(presentSupport){
      indices.family_presentation = i;
    }

    //Break if complete
    if(indices.is_complete()){
      break;
    }

    i++;
  }

  //---------------------------
  return indices;
}
std::vector<char> Engine_vulkan::read_file(const std::string& filename){
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  //---------------------------

  if (!file.is_open()) {
    throw std::runtime_error("[error] failed to open file!");
  }

  size_t fileSize = (size_t) file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  //---------------------------
  return buffer;
}

//Swap chain settings
VkSurfaceFormatKHR Engine_vulkan::swapChain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats){
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : availableFormats){
    if(format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      return format;
    }
  }

  //---------------------------
  return availableFormats[0];
}
VkPresentModeKHR Engine_vulkan::swapChain_presentation_mode(const std::vector<VkPresentModeKHR>& availablePresentModes){
  //4 possible modes:
  //- VK_PRESENT_MODE_IMMEDIATE_KHR
  //- VK_PRESENT_MODE_FIFO_KHR
  //- VK_PRESENT_MODE_FIFO_RELAXED_KHR
  //- VK_PRESENT_MODE_MAILBOX_KHR
  //---------------------------

  //Check for VK_PRESENT_MODE_MAILBOX_KHR mode
  for(const auto& mode : availablePresentModes){
    if(mode == VK_PRESENT_MODE_MAILBOX_KHR){
      return mode;
    }
  }

  //---------------------------
  return VK_PRESENT_MODE_FIFO_KHR;
}
VkExtent2D Engine_vulkan::swapChain_extent_setting(const VkSurfaceCapabilitiesKHR& capabilities){
  //Resolution of the swap chain image
  VkExtent2D extent;
  //---------------------------

  if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
    extent = capabilities.currentExtent;
  }else{
    glm::vec2 fbo_dim = engine_window->get_framebuffer_size();

    extent = {
      static_cast<uint32_t>(fbo_dim.x),
      static_cast<uint32_t>(fbo_dim.y)
    };

    extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
  }

  //---------------------------
  return extent;
}
void Engine_vulkan::recreate_swapChain(){
  //---------------------------

  vkDeviceWaitIdle(device);

  this->cleanup_swapChain();

  create_swapChain();
  create_image_views();
  create_framebuffers();

  //---------------------------
}
void Engine_vulkan::cleanup_swapChain(){
  //---------------------------

  for(size_t i=0; i<swapChain_fbo.size(); i++){
    vkDestroyFramebuffer(device, swapChain_fbo[i], nullptr);
  }

  for(size_t i=0; i<swapChain_image_views.size(); i++){
    vkDestroyImageView(device, swapChain_image_views[i], nullptr);
  }

  vkDestroySwapchainKHR(device, swapChain, nullptr);

  //---------------------------
}

//Graphics pipeline
VkShaderModule Engine_vulkan::create_shader_module(const std::vector<char>& code){
  //Shader modules are just a thin wrapper around the shader bytecode
  //---------------------------

  //Shader module info
  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

  //Shader module creation
  VkShaderModule shaderModule;
  VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("[error] failed to create shader module!");
  }

  //---------------------------
  return shaderModule;
}
void Engine_vulkan::record_command_buffer(VkCommandBuffer commandBuffer, uint32_t imageIndex){
  //---------------------------

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = 0; // Optional
  beginInfo.pInheritanceInfo = nullptr; // Optional

  VkResult result = vkBeginCommandBuffer(commandBuffer, &beginInfo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //Starting a render pass
  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass;
  renderPassInfo.framebuffer = swapChain_fbo[imageIndex];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = swapChain_extent;
  VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
  renderPassInfo.clearValueCount = 1;
  renderPassInfo.pClearValues = &clearColor;

  vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
  vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

  //Dynamic commands
  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = static_cast<float>(swapChain_extent.width);
  viewport.height = static_cast<float>(swapChain_extent.height);
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = swapChain_extent;
  vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

  vkCmdDraw(commandBuffer, 3, 1, 0, 0);
  vkCmdEndRenderPass(commandBuffer);

  result = vkEndCommandBuffer(commandBuffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }


  //---------------------------
}

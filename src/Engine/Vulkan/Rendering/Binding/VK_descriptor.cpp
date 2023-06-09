#include "VK_descriptor.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"

//Step for descriptor sets
//-create descriptor set layout
//-allocate descriptor set
//-create uniform object
//-update descriptor set
//-update uniform data
//-bind descriptor set


//Constructor / Destructor
VK_descriptor::VK_descriptor(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();

  this->pool_nb_descriptor = 1000;
  this->pool_nb_uniform = 1000;
  this->pool_nb_sampler = 100;

  //---------------------------
}
VK_descriptor::~VK_descriptor(){}

//Main function
void VK_descriptor::clean_descriptor_pool(){
  //---------------------------

  vkDestroyDescriptorPool(vk_param->device.device, descriptor_pool, nullptr);

  //---------------------------
}

//Descriptor set allocation
void VK_descriptor::allocate_descriptor_set(vector<VkDescriptorSetLayout>& vec_layout, vector<VkDescriptorSet>& vec_descriptor_set){
  //---------------------------

  VkDescriptorSetAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocation_info.descriptorPool = descriptor_pool;
  allocation_info.descriptorSetCount = static_cast<uint32_t>(vec_layout.size());
  allocation_info.pSetLayouts = vec_layout.data();

  vec_descriptor_set.resize(vec_layout.size());
  VkResult result = vkAllocateDescriptorSets(vk_param->device.device, &allocation_info, vec_descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}
void VK_descriptor::allocate_descriptor_set(Struct_binding* binding){
  //---------------------------

  VkDescriptorSetLayout& layout = binding->descriptor.layout;
  VkDescriptorSet& descriptor_set = binding->descriptor.set;

  VkDescriptorSetAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocation_info.descriptorPool = descriptor_pool;
  allocation_info.descriptorSetCount = 1;
  allocation_info.pSetLayouts = &layout;

  VkResult result = vkAllocateDescriptorSets(vk_param->device.device, &allocation_info, &descriptor_set);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}

//Descriptor set update
void VK_descriptor::update_descriptor_uniform(Struct_binding* binding){
  //---------------------------

  //Make list of writeable uniform
  vector<VkWriteDescriptorSet> vec_descriptor_write;
  vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;
  for(int i=0; i<binding->vec_uniform.size(); i++){
    Struct_uniform* uniform = binding->vec_uniform[i];

    VkDescriptorBufferInfo descriptor_info = {};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = uniform->size;
    vec_descriptor_buffer_info.push_back(descriptor_info);

    VkWriteDescriptorSet write_uniform = {};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = binding->descriptor.set;
    write_uniform.dstBinding = uniform->binding;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = TYPE_UNIFORM;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &vec_descriptor_buffer_info[i];
    vec_descriptor_write.push_back(write_uniform);
  }

  //Update descriptor
  if(vec_descriptor_write.size() != 0){
    vkUpdateDescriptorSets(vk_param->device.device, static_cast<uint32_t>(vec_descriptor_write.size()), vec_descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}
void VK_descriptor::update_descriptor_sampler(Struct_binding* binding, vector<Struct_image*> vec_image){
  //---------------------------

  //For each sampler strcut in binding struct search for image with same name in vec_image
  //and then update the corresponding shader sampler
  vector<VkWriteDescriptorSet> vec_descriptor_write;
  vector<VkDescriptorImageInfo> vec_descriptor_image_info;
  for(int i=0; i<binding->vec_sampler.size(); i++){
    Struct_sampler* sampler = binding->vec_sampler[i];

    for(int j=0; j<vec_image.size(); j++){
      Struct_image* image = vec_image[j];

      if(sampler->name == image->name){
        VkDescriptorImageInfo image_info = {};
        image_info.imageLayout = image->layout;
        image_info.imageView = image->view;
        image_info.sampler = image->sampler;
        vec_descriptor_image_info.push_back(image_info);

        VkWriteDescriptorSet write_sampler = {};
        write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write_sampler.dstSet = binding->descriptor.set;
        write_sampler.dstBinding = sampler->binding;
        write_sampler.dstArrayElement = 0;
        write_sampler.descriptorType = TYPE_SAMPLER;
        write_sampler.descriptorCount = 1;
        write_sampler.pImageInfo = &vec_descriptor_image_info[vec_descriptor_image_info.size()-1];
        vec_descriptor_write.push_back(write_sampler);
      }
    }
  }

  if(vec_descriptor_write.size() != 0){
    vkUpdateDescriptorSets(vk_param->device.device, static_cast<uint32_t>(vec_descriptor_write.size()), vec_descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}

//Descriptor layout
void VK_descriptor::create_layout_from_required(Struct_binding* binding){
  vec_descriptor_required& vec_required_binding = binding->vec_required_binding;
  VkDescriptorSetLayout& layout = binding->descriptor.layout;
  //---------------------------

  vector<VkDescriptorSetLayoutBinding> vec_binding;
  for(int i=0; i<vec_required_binding.size(); i++){
    descriptor_required& req_binding = vec_required_binding[i];

    //Get descriptor elements
    int binding = get<2>(req_binding);
    VkDescriptorType type = get<3>(req_binding);
    VkShaderStageFlagBits stage = get<4>(req_binding);

    //Convert it into descriptor binding
    VkDescriptorSetLayoutBinding layout_binding = add_descriptor_binding(type, stage, 1, binding);
    vec_binding.push_back(layout_binding);
  }

  //Create descriptor layout from requirements
  layout = create_layout(vec_binding);

  //---------------------------

}
VkDescriptorSetLayout VK_descriptor::create_layout(vector<VkDescriptorSetLayoutBinding>& vec_binding){
  //---------------------------

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_binding.size());
  layoutInfo.pBindings = vec_binding.data();

  //Descriptor set layout creation
  VkDescriptorSetLayout descriptor_layout;
  VkResult result = vkCreateDescriptorSetLayout(vk_param->device.device, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  //---------------------------
  return descriptor_layout;
}
VkDescriptorSetLayoutBinding VK_descriptor::add_descriptor_binding(VkDescriptorType type, VkShaderStageFlagBits stage, int count, int binding){
  //---------------------------

  VkDescriptorSetLayoutBinding layout_binding{};
  layout_binding.binding = binding;
  layout_binding.descriptorCount = static_cast<uint32_t>(count);
  layout_binding.descriptorType = type;
  layout_binding.stageFlags = stage;
  layout_binding.pImmutableSamplers = nullptr; // Optional

  //---------------------------
  return layout_binding;
}

//Descriptor pool
void VK_descriptor::create_descriptor_pool(){
  //---------------------------

  //Maximum number of descriptor per type
  vector<VkDescriptorPoolSize> vec_pool_size;
  vec_pool_size.push_back(add_descriptor_type(TYPE_UNIFORM, pool_nb_uniform));
  vec_pool_size.push_back(add_descriptor_type(TYPE_SAMPLER, pool_nb_sampler));

  VkDescriptorPoolCreateInfo pool_info{};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.poolSizeCount = static_cast<uint32_t>(vec_pool_size.size());
  pool_info.pPoolSizes = vec_pool_size.data();
  pool_info.maxSets = static_cast<uint32_t>(pool_nb_descriptor);

  VkResult result = vkCreateDescriptorPool(vk_param->device.device, &pool_info, nullptr, &descriptor_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor pool!");
  }

  //---------------------------
}
VkDescriptorPoolSize VK_descriptor::add_descriptor_type(VkDescriptorType type, int count){
  //---------------------------

  VkDescriptorPoolSize pool_sampler{};
  pool_sampler.type = type;
  pool_sampler.descriptorCount = static_cast<uint32_t>(count);

  //---------------------------
  return pool_sampler;
}

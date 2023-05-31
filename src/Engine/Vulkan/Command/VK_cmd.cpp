#include "VK_cmd.h"

#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Instance/Element/VK_gui.h"
#include "../Pipeline/VK_pipeline.h"
#include "../Data/VK_buffer.h"
#include "../Presentation/Swapchain/VK_frame.h"
#include "../Camera/VK_camera.h"
#include "../Camera/VK_viewport.h"
#include "../Shader/Binding/VK_binding.h"
#include "../Rendering/VK_canvas.h"
#include "../Data/VK_data.h"


//Constructor / Destructor
VK_cmd::VK_cmd(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_camera = vk_engine->get_vk_camera();
  this->vk_canvas = vk_engine->get_vk_canvas();
  this->vk_binding = vk_engine->get_vk_binding();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_viewport = vk_engine->get_vk_viewport();

  //---------------------------
}
VK_cmd::~VK_cmd(){}

//Renderpass commands
void VK_cmd::cmd_viewport(VkCommandBuffer command_buffer){
  //---------------------------

  vk_viewport->update_viewport(vk_param->window.extent);

  VkViewport viewport = vk_viewport->get_viewport();
  VkRect2D scissor = vk_viewport->get_scissor();

  vkCmdSetViewport(command_buffer, 0, 1, &viewport);
  vkCmdSetScissor(command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_cmd::cmd_drawing_scene(VkCommandBuffer command_buffer){
  //---------------------------

  //Object
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("scene");

  //Pipeline
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "point"){
      //Camera
      vk_camera->compute_mvp(object);
      vk_binding->update_uniform(data);
      vkCmdBindDescriptorSets(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &data->binding.descriptor.set, 0, nullptr);

      //Data
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_cmd::cmd_drawing_glyph(VkCommandBuffer command_buffer){
  //---------------------------

  //Object
  list<Struct_data*> list_data_glyph = vk_data->get_list_data_glyph();
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("glyph");

  //Pipine
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data =  *next(list_data_glyph.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "line"){
      //Camera
      vk_camera->compute_mvp(object);
      vk_binding->update_uniform(data);
      vkCmdBindDescriptorSets(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &data->binding.descriptor.set, 0, nullptr);

      //Data
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdSetLineWidth(command_buffer, object->draw_line_width);
      vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_cmd::cmd_drawing_canvas(VkCommandBuffer command_buffer){
  //---------------------------

  //Object
  Struct_data* data_canvas = vk_canvas->get_canvas();
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName("canvas");
  Object* canvas = data_canvas->object;

  //Pipeline
  vkCmdBindPipeline(command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Camera
  vk_camera->compute_mvp(canvas);
  vkCmdPushConstants(command_buffer, pipeline->pipeline_layout, STAGE_VS, 0, sizeof(glm::mat4), &canvas->mvp);

  //Data
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(command_buffer, 0, 1, &data_canvas->xyz.vbo, offsets);
  vkCmdBindVertexBuffers(command_buffer, 2, 1, &data_canvas->uv.vbo, offsets);
  vkCmdDraw(command_buffer, canvas->xyz.size(), 1, 0, 0);

  //---------------------------
}

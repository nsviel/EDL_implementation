#include "VK_cmd.h"
#include "VK_command.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Instance/Element/VK_gui.h"
#include "../../Pipeline/Pipeline/VK_pipeline.h"
#include "../../Data/VK_buffer.h"
#include "../../Presentation/Swapchain/VK_frame.h"
#include "../../Presentation/Camera/VK_camera.h"
#include "../../Presentation/Camera/VK_viewport.h"
#include "../../Shader/Binding/VK_binding.h"
#include "../../Shader/Descriptor/VK_descriptor.h"
#include "../../Pipeline/Rendering/VK_canvas.h"
#include "../../Data/VK_data.h"


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

//Main function
void VK_cmd::cmd_record_scene(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  vk_command->start_render_pass(renderpass);
  this->cmd_viewport(renderpass);
  this->cmd_drawing_scene(renderpass);
  this->cmd_drawing_glyph(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void VK_cmd::cmd_record_gui(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  VK_gui* vk_gui = vk_engine->get_vk_gui();
  //---------------------------

  vk_command->start_render_pass(renderpass);
  vk_gui->command_gui(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}
void VK_cmd::cmd_record_canvas(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  vk_command->start_render_pass(renderpass);
  this->cmd_viewport(renderpass);
  this->cmd_drawing_canvas(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
}

//Renderpass commands
void VK_cmd::cmd_viewport(Struct_renderpass* renderpass){
  //---------------------------

  vk_viewport->update_viewport(vk_param->window.extent);

  VkViewport viewport = vk_viewport->get_viewport();
  VkRect2D scissor = vk_viewport->get_scissor();

  vkCmdSetViewport(renderpass->command_buffer, 0, 1, &viewport);
  vkCmdSetScissor(renderpass->command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_cmd::cmd_drawing_scene(Struct_renderpass* renderpass){
  //---------------------------

  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "topology_point");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "point"){
      //Camera
      vk_camera->compute_mvp(object);
      vk_binding->update_uniform(&pipeline->binding, data->object->mvp);

      VK_descriptor* vk_descriptor = vk_engine->get_vk_descriptor();
      list<Struct_image*> vec_image;
      vk_descriptor->update_descriptor_set(&pipeline->binding, vec_image);

      vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

      //Data
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(renderpass->command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_cmd::cmd_drawing_glyph(Struct_renderpass* renderpass){
  //---------------------------

  //Pipine
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "topology_line");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Bind and draw vertex buffers
  list<Struct_data*> list_data_glyph = vk_data->get_list_data_glyph();
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data =  *next(list_data_glyph.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "line"){
      //Camera
      vk_camera->compute_mvp(object);
      vk_binding->update_uniform(&pipeline->binding, data->object->mvp);

      vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

      //Data
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdSetLineWidth(renderpass->command_buffer, object->draw_line_width);
      vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(renderpass->command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_cmd::cmd_drawing_canvas(Struct_renderpass* renderpass){
  //---------------------------

  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "topology_triangle");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  //Object
  Struct_data* data = vk_canvas->get_canvas();
  Object* canvas = data->object;

/*
  Frame* offscreen = vk_param->renderpass_scene.frame_set->get_frame_inflight();
  if(data->binding.list_texture.size() <3){
    data->binding.list_texture.push_back(&offscreen->color);
  }else{
    Struct_image* image =  *next(data->binding.list_texture.begin(),2);
    image = &offscreen->color;
  }
  VK_descriptor* vk_descriptor = vk_engine->get_vk_descriptor();
  vk_descriptor->update_descriptor_set(&data->binding);
*/

  //Frame* frame = renderpass->frame_set->get_frame_inflight();
  //Struct_image* texture = *next(data->binding.list_texture.begin(), 0);
  //texture->image = frame->color;



  //Descriptor
  vk_camera->compute_mvp(canvas);
  //vk_binding->update_uniform(&data->binding, data->object->mvp);
  vk_binding->update_uniform(&pipeline->binding, data->object->mvp);
  vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline_layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

  //Data
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 1, &data->xyz.vbo, offsets);
  vkCmdBindVertexBuffers(renderpass->command_buffer, 2, 1, &data->uv.vbo, offsets);
  vkCmdDraw(renderpass->command_buffer, canvas->xyz.size(), 1, 0, 0);

  //---------------------------
}

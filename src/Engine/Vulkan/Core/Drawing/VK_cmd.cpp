#include "VK_cmd.h"

#include "../Command/VK_command.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Instance/Element/VK_gui.h"
#include "../../Core/Pipeline/VK_pipeline.h"
#include "../../Data/VK_buffer.h"
#include "../../Presentation/Swapchain/VK_frame.h"
#include "../../Presentation/Camera/VK_camera.h"
#include "../../Presentation/Camera/VK_viewport.h"
#include "../../Render/Binding/VK_descriptor.h"
#include "../../Render/Binding/VK_uniform.h"
#include "../../Render/Canvas/VK_canvas.h"
#include "../../Data/VK_data.h"

#include "../../../Node_engine.h"
#include "../../../Shader/Shader.h"
#include "../../../Shader/Source/EDL/Shader_edl.h"


//Constructor / Destructor
VK_cmd::VK_cmd(VK_engine* vk_engine){
  //---------------------------

  Node_engine* node_engine = vk_engine->get_node_engine();
  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_camera = vk_engine->get_vk_camera();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_gui = vk_engine->get_vk_gui();

  this->vk_canvas = vk_engine->get_vk_canvas();

  Shader* shaderManager = node_engine->get_shaderManager();
  this->shader_edl = shaderManager->get_shader_edl();

  //---------------------------
}
VK_cmd::~VK_cmd(){}

//Main function
void VK_cmd::cmd_record_psr(Struct_renderpass* renderpass){
  Frame* frame = renderpass->get_rendering_frame();
  //---------------------------

  vk_command->start_render_pass(renderpass, frame, false);
  this->cmd_viewport(renderpass, vk_viewport->get_viewport_canvas());
  this->cmd_draw_psr(renderpass);
  vk_command->stop_render_pass(renderpass);

  //---------------------------
  frame->color.name = "tex_color_psr";
  frame->depth.name = "tex_depth_psr";
}


//Renderpass commands
void VK_cmd::cmd_viewport(Struct_renderpass* renderpass, VkViewport viewport){
  //---------------------------

  //Viewport
  vkCmdSetViewport(renderpass->command_buffer, 0, 1, &viewport);

  //Scissor
  VkRect2D scissor = vk_viewport->get_scissor();
  vkCmdSetScissor(renderpass->command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_cmd::cmd_draw_psr(Struct_renderpass* renderpass){
  //---------------------------
/*
  //Pipeline
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "triangle");
  vkCmdBindPipeline(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->pipeline);

  shader_edl->update_shader();
  Struct_edl* edl_param = shader_edl->get_edl_param();

  //Descriptor
  vk_uniform->update_uniform_edl("Struct_pyramid", &pipeline->binding, *edl_param);
  vkCmdBindDescriptorSets(renderpass->command_buffer, PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

  //Data
  Struct_data* data = vk_canvas->get_data_canvas();
  Object* canvas = data->object;
  VkDeviceSize offsets[] = {0};
  vkCmdBindVertexBuffers(renderpass->command_buffer, 0, 1, &data->xyz.vbo, offsets);
  vkCmdBindVertexBuffers(renderpass->command_buffer, 2, 1, &data->uv.vbo, offsets);
  vkCmdDraw(renderpass->command_buffer, canvas->xyz.size(), 1, 0, 0);
*/
  //---------------------------
}

//Secondary command buffer
void VK_cmd::cmd_record_scene_secondcb(Struct_renderpass* renderpass){
  //---------------------------
/*
  //Bind and draw vertex buffers
  list<Struct_data*> list_data_scene = vk_data->get_list_data_scene();
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data =  *next(list_data_scene.begin(),i);
    Object* object = data->object;

    if(object->draw_type_name == "point"){
      VkBuffer vertexBuffers[] = {data->xyz.vbo, data->rgb.vbo};
      VkDeviceSize offsets[] = {0, 0};

      vkResetCommandBuffer(data->command_buffer_secondary, 0);
      vk_command->start_command_buffer_secondary(renderpass, data->command_buffer_secondary);

      Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, "point");
      vkCmdBindPipeline(data->command_buffer_secondary, PIPELINE_GRAPHICS, pipeline->pipeline);

      this->cmd_viewport(data->command_buffer_secondary);
      this->cmd_scissor(data->command_buffer_secondary);

      //vk_camera->compute_mvp(object);
      //vk_uniform->update_uniform_mat4("mvp", &pipeline->binding, data->object->mvp);
      vkCmdBindDescriptorSets(data->command_buffer_secondary, PIPELINE_GRAPHICS, pipeline->layout, 0, 1, &pipeline->binding.descriptor.set, 0, nullptr);

      vkCmdBindVertexBuffers(data->command_buffer_secondary, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(data->command_buffer_secondary, object->xyz.size(), 1, 0, 0);

      vk_command->stop_command_buffer(data->command_buffer_secondary);
    }
  }
*/
  //---------------------------
}

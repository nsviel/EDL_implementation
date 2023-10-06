#include "GUI_engine.h"
#include <GUI.h>
#include "../Window/Control/GUI_control.h"
#include <Render/Render_node.h>
#include <Render/Vulkan/VK_engine.h>
#include <Render/Vulkan/VK_param.h>


//Constructor / Destructor
GUI_engine::GUI_engine(GUI* gui){
  //---------------------------

  Render_node* render_node = gui->get_node_render();
  VK_engine* vk_engine = render_node->get_vk_engine();
  this->vk_param = vk_engine->get_vk_param();
  this->gui_control = gui->get_gui_control();

  //---------------------------
}
GUI_engine::~GUI_engine(){}

//Main function
void GUI_engine::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Engine");
  this->engine_window();
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void GUI_engine::engine_window(){
  //---------------------------

  //Vraiment deguelasse,a changer au plus vite !!
  static ImVec2 previous_size;
  ImVec2 current_size = ImGui::GetWindowSize();
  if (current_size.x != previous_size.x || current_size.y != previous_size.y){
    has_been_initialized = false;
    previous_size = current_size;
  }

  if(has_been_initialized == false){
    for(int i=0; i<vk_param->nb_frame; i++){
      Frame* frame_edl = vk_param->renderpass_edl.get_rendering_frame();
      Struct_image* image = &frame_edl->color;
      this->descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
    }
    has_been_initialized = true;
  }

  Frame* frame_edl = vk_param->renderpass_edl.get_rendering_frame();
  Struct_image* image = &frame_edl->color;
  this->descriptor = ImGui_ImplVulkan_AddTexture(image->sampler, image->view, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
  ImGui::Image(descriptor, ImVec2{viewportPanelSize.x, viewportPanelSize.y});

  if(ImGui::IsItemHovered()){
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImVec2 center = ImVec2(windowPos.x + windowSize.x * 0.5f, windowPos.y + windowSize.y * 0.5f);

    gui_control->make_control(center);
  }

  //---------------------------
}

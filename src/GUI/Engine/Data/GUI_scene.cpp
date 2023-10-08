#include "GUI_scene.h"

#include <GUI.h>
#include <GUI_param.h>
#include <Data/Data_node.h>
#include <Data/Scene/Database.h>
#include <Engine/Data/GUI_object.h>
#include <Engine/Data/GUI_set.h>


//Constructor / Destructor
GUI_scene::GUI_scene(GUI* gui){
  //---------------------------

  Data_node* data_node = gui->get_data_node();
  this->dataManager = data_node->get_dataManager();
  this->gui_param = gui->get_gui_param();
  this->gui_object = gui->get_gui_object();
  this->gui_set = gui->get_gui_set();

  //---------------------------
}
GUI_scene::~GUI_scene(){}

//Main function
void GUI_scene::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Object");
  this->draw_window_background();
  this->tree_view();
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void GUI_scene::draw_window_background(){
  //-------------------------------

  float x1 = ImGui::GetCurrentWindow()->WorkRect.Min.x;
  float x2 = ImGui::GetCurrentWindow()->WorkRect.Max.x;
  float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
  float item_offset_y = -item_spacing_y * 0.1f;
  float line_height = ImGui::GetTextLineHeight() + item_spacing_y;
  int row_count = 50;
  ImU32 col_even = IM_COL32(35, 35, 35, 255);
  ImU32 col_odd = IM_COL32(25, 25, 25, 255);

  ImDrawList* draw_list = ImGui::GetWindowDrawList();
  float y0 = ImGui::GetCursorScreenPos().y + (float)(int)item_offset_y;

  int row_display_start;
  int row_display_end;
  ImGui::CalcListClipping(row_count, line_height, &row_display_start, &row_display_end);
  for (int row_n = row_display_start; row_n < row_display_end; row_n++)
  {
      ImU32 col = (row_n & 1) ? col_odd : col_even;
      if ((col & IM_COL32_A_MASK) == 0)
          continue;
      float y1 = y0 + (line_height * row_n);
      float y2 = y1 + line_height;
      draw_list->AddRectFilled(ImVec2(x1, y1), ImVec2(x2, y2), col);
  }

  //-------------------------------
}
void GUI_scene::tree_view(){
  list<Set*>* list_data = dataManager->get_list_data_scene();
  //---------------------------
//say("----");
  static ImGuiTableFlags flag_tree;
  flag_tree |= ImGuiTableFlags_SizingFixedFit;
  flag_tree |= ImGuiTableFlags_NoBordersInBody;
  flag_tree |= ImGuiTableFlags_SizingFixedSame;


  if(ImGui::BeginTable("data_view", 1)){

    //Database
    for(int row_i=0; row_i<list_data->size(); row_i++){
      Set* set = *next(list_data->begin(), row_i);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();

      ImGui::PushID(set->name.c_str());
      this->data_node_tree(set);
      ImGui::PopID();
    }

    ImGui::EndTable();
  }

  //---------------------------
}
int GUI_scene::data_node_tree(Set* set){
  int nb_row = 0;
  //-------------------------------

  //Node flag_tree
  ImGuiTreeNodeFlags flag_node;
  flag_node |= ImGuiTreeNodeFlags_OpenOnArrow;
  //flag_node |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
  if(set->name != "Glyph"){
    flag_node |= ImGuiTreeNodeFlags_DefaultOpen;
  }

  //Leaf flag_tree
  ImGuiTreeNodeFlags flag_leaf;
  flag_leaf |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag_leaf |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
  flag_leaf |= ImGuiTreeNodeFlags_Leaf;
  flag_leaf |= ImGuiTreeNodeFlags_NoTreePushOnOpen;
  flag_leaf |= ImGuiTreeNodeFlags_Bullet;
  flag_leaf |= ImGuiTreeNodeFlags_SpanFullWidth;

  //Set nodes
  bool is_node_open = ImGui::TreeNodeEx(set->name.c_str(), flag_node);

  //If item double-clicked
  if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
    gui_set->set_selected_set(set);
    gui_param->show_set = true;
  }

  //Set elements leaf nodes
  if(is_node_open){
    for(int j=0; j<set->list_obj.size(); j++){
      Object* object = *next(set->list_obj.begin(), j);

      ImGui::TableNextRow();
      ImGui::TableNextColumn();
      nb_row++;

      //If object is selected
      if(object->ID == set->selected_obj->ID && set->name == "Object"){
        flag_leaf |= ImGuiTreeNodeFlags_Selected;
      }else{
        flag_leaf &= ~ImGuiTreeNodeFlags_Selected;
      }

      //Display leaf
      ImGui::TreeNodeEx(object->name.c_str(), flag_leaf);

      //If item clicked
      if(ImGui::IsItemClicked()){
        set->selected_obj = object;
      }

      //If item double-clicked
      if(ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)){
        gui_object->set_selected_object(object);
        gui_param->show_object = true;
      }

    }

    ImGui::TreePop();
  }

  //-------------------------------
  return nb_row;
}

#include "GUI_filemanager.h"

#include "../Node_gui.h"

#include "../../Data/Node_data.h"
#include "../../Data/Scene/Database.h"


//Constructor / Destructor
GUI_filemanager::GUI_filemanager(Node_gui* node_gui){
  //---------------------------

  Node_data* node_data = node_gui->get_node_data();
  this->dataManager = node_data->get_dataManager();

  //---------------------------
}
GUI_filemanager::~GUI_filemanager(){}

//Main function
void GUI_filemanager::tree_view(float width){
  list<Set*>* list_data = dataManager->get_list_data_scene();
  //---------------------------

  static ImGuiTableFlags flag_tree;
  flag_tree |= ImGuiTableFlags_BordersOuterH;
  flag_tree |= ImGuiTableFlags_SizingFixedFit;
  flag_tree |= ImGuiTableFlags_RowBg;
  flag_tree |= ImGuiTableFlags_NoBordersInBody;
  flag_tree |= ImGuiTableFlags_SizingFixedSame;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::BeginTable("data_view", 1, flag_tree);
  ImGui::TableSetupColumn("Column 1", ImGuiTableColumnFlags_WidthFixed, width);

  //Database
  int nb_row = 0;
  for(int row_i=0; row_i<list_data->size(); row_i++){
    Set* set = *next(list_data->begin(), row_i);

    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    nb_row++;

    ImGui::PushID(set->name.c_str());
    nb_row += data_node_tree(set);
    ImGui::PopID();

  }
  for(int i=0; i<6-nb_row; i++){
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text(" ");
  }

  ImGui::EndTable();
  ImGui::PopStyleVar();

  //---------------------------
}
int GUI_filemanager::data_node_tree(Set* set){
  int nb_row = 0;
  //-------------------------------

  //Node flag_tree
  ImGuiTreeNodeFlags flag_node;
  flag_node |= ImGuiTreeNodeFlags_OpenOnArrow;
  flag_node |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
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

      //If clicked by mouse
      if(ImGui::IsItemClicked()){
        set->selected_obj = object;
      }

    }

    ImGui::TreePop();
  }

  //-------------------------------
  return nb_row;
}

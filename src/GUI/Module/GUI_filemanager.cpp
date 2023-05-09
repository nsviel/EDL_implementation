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
void GUI_filemanager::tree_view(){
  list<Set*>* list_data = dataManager->get_list_data();
  //---------------------------

  static ImGuiTableFlags flags;
  flags |= ImGuiTableFlags_BordersOuterH;
  flags |= ImGuiTableFlags_SizingFixedFit;
  flags |= ImGuiTableFlags_RowBg;
  flags |= ImGuiTableFlags_NoBordersInBody;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::BeginTable("data_view", 3, flags);

  //Database
  for(int row_i=0; row_i<list_data->size(); row_i++){
    Set* set = *next(list_data->begin(), row_i);
    //----------

    //Set table row
    ImGui::TableNextRow();
    ImGui::PushID(row_i);

    //Cloud name
    ImGui::TableNextColumn();
    this->data_node(set);

    //----------
    ImGui::PopID();
  }
  for(int i=0; i<6; i++){
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text(" ");
  }

  ImGui::EndTable();
  ImGui::PopStyleVar();

  //---------------------------
}
void GUI_filemanager::data_node(Set* set){
  //-------------------------------

  ImGuiTreeNodeFlags node_flags;
  node_flags |= ImGuiTreeNodeFlags_OpenOnArrow;
  node_flags |= ImGuiTreeNodeFlags_OpenOnDoubleClick;
  node_flags |= ImGuiTreeNodeFlags_DefaultOpen;

  /*if(selected_col->ID_col_order == collection->ID_col_order){
    node_flags |= ImGuiTreeNodeFlags_Selected;
  }*/

  bool is_node_open = ImGui::TreeNodeEx(set->name.c_str(), node_flags);

  //If clicked by mouse
  if(ImGui::IsItemClicked()){
    //data->set_selected_collection(collection);
  }

  //Subset tree node
  if(is_node_open && set != nullptr && (set->list_obj.size() > 0)){

    //this->info_collection(collection);

    for(int j=0; j<set->list_obj.size(); j++){
      Object* object = *next(set->list_obj.begin(), j);

      node_flags |= ImGuiTreeNodeFlags_Leaf;
      node_flags |= ImGuiTreeNodeFlags_Bullet;

      bool is_node_open = ImGui::TreeNodeEx(object->name.c_str(), node_flags);
      if(is_node_open){
        //this->info_object(object);
        ImGui::TreePop();
      }

      //If clicked by mouse
      if(ImGui::IsItemClicked()){
        //graphManager->object_clicked(collection, j);
      }
    }
  }

  //-------------------------------
}
